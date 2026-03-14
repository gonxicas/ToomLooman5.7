#include "RogueAttributeSet.h"

URogueHealthAttributeSet::URogueHealthAttributeSet() : Health(FRogueAttribute(100)),
                                                       HealthMax(FRogueAttribute(Health.GetValue()))
{
}

