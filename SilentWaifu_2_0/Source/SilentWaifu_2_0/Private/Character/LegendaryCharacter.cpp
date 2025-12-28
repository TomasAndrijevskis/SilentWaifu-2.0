
#include "Character/LegendaryCharacter.h"
#include "Character/Abilities/AbilityComponent_Base.h"
#include "Character/Abilities/AbilityComponent_Legendary.h"


ALegendaryCharacter::ALegendaryCharacter()
{
	AbilityComponent = CreateDefaultSubobject<UAbilityComponent_Legendary>(TEXT("Ability Component"));
}
