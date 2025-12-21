
#include "Character/VeryRareCharacter.h"
#include "Character/Abilities/AbilityComponent_Base.h"


AVeryRareCharacter::AVeryRareCharacter()
{
	AbilityComponent = CreateDefaultSubobject<UAbilityComponent_Base>(TEXT("Ability Component"));
}
