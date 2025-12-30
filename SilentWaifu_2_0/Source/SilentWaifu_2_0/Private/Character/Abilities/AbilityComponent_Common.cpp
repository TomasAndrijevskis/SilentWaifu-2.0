
#include "Character/Abilities/AbilityComponent_Common.h"


void UAbilityComponent_Common::Action()
{
	Super::Action();
}


int UAbilityComponent_Common::GetAbilityDuration() const
{
	return DurationHours;
}