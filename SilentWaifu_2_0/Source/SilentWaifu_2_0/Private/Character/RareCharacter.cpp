
#include "Character/RareCharacter.h"
#include "Character/Abilities/AbilityComponent_Base.h"


ARareCharacter::ARareCharacter()
{
	AbilityComponent = CreateDefaultSubobject<UAbilityComponent_Base>(TEXT("Ability Component"));
}
