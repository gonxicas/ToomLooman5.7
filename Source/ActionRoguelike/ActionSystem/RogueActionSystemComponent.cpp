#include "RogueActionSystemComponent.h"

#include "RogueAction.h"
#include "RogueAttributeSet.h"
#include "SharedGameplayTags.h"


URogueActionSystemComponent::URogueActionSystemComponent()
{
	bWantsInitializeComponent = true;

	AttributeSetClass = URogueAttributeSet::StaticClass();
}

void URogueActionSystemComponent::InitializeComponent()
{
	Super::InitializeComponent();

	Attributes = NewObject<URogueAttributeSet>(this, AttributeSetClass);

	for (TFieldIterator<FStructProperty> PropIt(Attributes->GetClass()); PropIt; ++PropIt)
	{
		auto FoundAttribute = PropIt->ContainerPtrToValuePtr<FRogueAttribute>(Attributes);

		FName AttributeTagName("Attribute." + PropIt->GetName());
		auto AttributeTag = FGameplayTag::RequestGameplayTag(AttributeTagName);

		CachedAttributes.Add(AttributeTag, FoundAttribute);
	}

	for (const TSubclassOf<URogueAction> ActionClass : DefaultActions)
	{
		if (ensure(ActionClass))
		{
			GrantAction(ActionClass);
		}
	}
	
}

void URogueActionSystemComponent::BeginPlay()
{
	Super::BeginPlay();
	
	Attributes->InitializeAttribute();
}

void URogueActionSystemComponent::StartAction(FGameplayTag InActionName)
{
	for (URogueAction* Action : Actions)
	{
		if (Action->GetActionName() == InActionName)
		{
			if (Action->CanStart())
			{
				Action->StartAction();
			}
			return;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("No action found with name %s"), *InActionName.ToString())
}

void URogueActionSystemComponent::StopAction(FGameplayTag InActionName)
{
	for (URogueAction* Action : Actions)
	{
		if (Action->GetActionName() == InActionName)
		{
			Action->StopAction();
			return;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("No action found with name %s"), *InActionName.ToString())
}

void URogueActionSystemComponent::GrantAction(TSubclassOf<URogueAction> NewActionClass)
{
	auto NewAction = NewObject<URogueAction>(this, NewActionClass);

	Actions.Add(NewAction);
}


void URogueActionSystemComponent::ApplyAttributeChange(FGameplayTag AttributeTag, const float Delta,
                                                       EAttributeModifyType ModifyType)
{
	auto FoundAttribute = GetAttribute(AttributeTag);
	check(FoundAttribute);

	auto OldValue = FoundAttribute->GetValue();

	switch (ModifyType)
	{
	case Base:
		FoundAttribute->Base += Delta;
		break;
	case Modifier:
		FoundAttribute->Modifier += Delta;
		break;
	case Override:
		FoundAttribute->Base = Delta;
		break;
	default:
		check(false);
	}

	Attributes->PostAttributeChanged();
	
	if (auto Event = AttributeListeners.Find(AttributeTag))
	{
		Event->Broadcast(AttributeTag, FoundAttribute->GetValue(), OldValue);
	}
	
	if (TArray<FOnAttributeDynamicChanged>* Events = AttributeDynamicListeners.Find(AttributeTag))
	{
		
		for (int i = Events->Num() - 1; i >= 0; --i)
		{
			FOnAttributeDynamicChanged& Event = (*Events)[i];
			bool bIsBound = Event.ExecuteIfBound(AttributeTag, FoundAttribute->GetValue(), OldValue);
			if (!bIsBound)
			{
				Events->RemoveAt(i);
				UE_LOG(LogTemp, Log, TEXT("cleaned up expired attribute delegate for %s"), *GetNameSafe(GetOwner()));
			}
		}
	}

	
	UE_LOGFMT(LogTemp, Log, "Attribute {0}, New: {1}, Old: {2}", AttributeTag.ToString(), FoundAttribute->GetValue(),
	          OldValue);
}

void URogueActionSystemComponent::AddDynamicAttributeListener(FOnAttributeDynamicChanged Event, FGameplayTag AttributeTag)
{
	TArray<FOnAttributeDynamicChanged>& Events = AttributeDynamicListeners.FindOrAdd(AttributeTag);
	Events.Add(Event);
}

void URogueActionSystemComponent::RemoveDynamicAttributeListener(FOnAttributeDynamicChanged Event)
{
	for (TPair<FGameplayTag, TArray<FOnAttributeDynamicChanged>>& Listener : AttributeDynamicListeners)
	{
		if (Listener.Value.RemoveSingle(Event) > 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("successfully removed blueprint binding"));
			break;
		}
	}
}

FRogueAttribute* URogueActionSystemComponent::GetAttribute(FGameplayTag InAttributeTag) const
{
	const auto FoundAttribute = *CachedAttributes.Find(InAttributeTag);

	return FoundAttribute;
}

float URogueActionSystemComponent::GetAttributeValue(FGameplayTag InAttributeTag) const
{
	return GetAttribute(InAttributeTag)->GetValue();
}

FOnAttributeChanged& URogueActionSystemComponent::GetAttributeListener(FGameplayTag AttributeTag)
{
	return AttributeListeners.FindOrAdd(AttributeTag);
}
