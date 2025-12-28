
#include "Character/RareCharacter.h"
#include "Character/Abilities/AbilityComponent_Base.h"
#include "Character/Abilities/AbilityComponent_Rare.h"


ARareCharacter::ARareCharacter()
{
	AbilityComponent = CreateDefaultSubobject<UAbilityComponent_Rare>(TEXT("Ability Component"));
}
