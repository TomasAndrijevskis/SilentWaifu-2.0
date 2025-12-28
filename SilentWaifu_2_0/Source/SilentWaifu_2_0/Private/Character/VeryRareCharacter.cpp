
#include "Character/VeryRareCharacter.h"
#include "Character/Abilities/AbilityComponent_Base.h"
#include "Character/Abilities/AbilityComponent_VeryRare.h"


AVeryRareCharacter::AVeryRareCharacter()
{
	AbilityComponent = CreateDefaultSubobject<UAbilityComponent_VeryRare>(TEXT("Ability Component"));
}
