#include "RoguePlayerController.h"

#include "EnhancedInputComponent.h"
#include "RogueInteractionComponent.h"


ARoguePlayerController::ARoguePlayerController()
{
	InteractionComponent = CreateDefaultSubobject<URogueInteractionComponent>(TEXT("InteractionComp"));
}

void ARoguePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent);
	
	EnhancedInput->BindAction(Input_Interact, ETriggerEvent::Triggered, this, &ARoguePlayerController::StartInteract);
}

void ARoguePlayerController::StartInteract()
{
	InteractionComponent->Interact();
}
