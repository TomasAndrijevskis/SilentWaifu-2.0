
#include "Character/EliteCharacter.h"
#include "Character/Abilities/AbilityComponent_Base.h"


AEliteCharacter::AEliteCharacter()
{
	AbilityComponent = CreateDefaultSubobject<UAbilityComponent_Base>(TEXT("Ability Component"));
}
