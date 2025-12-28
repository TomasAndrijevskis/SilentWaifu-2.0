
#include "Character/EliteCharacter.h"
#include "Character/Abilities/AbilityComponent_Base.h"
#include "Character/Abilities/AbilityComponent_Elite.h"


AEliteCharacter::AEliteCharacter()
{
	AbilityComponent = CreateDefaultSubobject<UAbilityComponent_Elite>(TEXT("Ability Component"));
}
