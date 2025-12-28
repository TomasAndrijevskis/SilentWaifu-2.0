
#include "Character/CommonCharacter.h"
#include "Character/Abilities/AbilityComponent_Base.h"
#include "Character/Abilities/AbilityComponent_Common.h"


ACommonCharacter::ACommonCharacter()
{
	AbilityComponent = CreateDefaultSubobject<UAbilityComponent_Common>(TEXT("Ability Component"));
}
