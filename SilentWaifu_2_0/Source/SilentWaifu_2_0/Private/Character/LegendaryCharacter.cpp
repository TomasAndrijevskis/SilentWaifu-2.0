
#include "Character/LegendaryCharacter.h"
#include "Character/Abilities/AbilityComponent_Base.h"


ALegendaryCharacter::ALegendaryCharacter()
{
	AbilityComponent = CreateDefaultSubobject<UAbilityComponent_Base>(TEXT("Ability Component"));
}
