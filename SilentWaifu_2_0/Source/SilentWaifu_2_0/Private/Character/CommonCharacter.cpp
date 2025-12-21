
#include "Character/CommonCharacter.h"
#include "Character/Abilities/AbilityComponent_Base.h"


ACommonCharacter::ACommonCharacter()
{
	AbilityComponent = CreateDefaultSubobject<UAbilityComponent_Base>(TEXT("Ability Component"));
}
