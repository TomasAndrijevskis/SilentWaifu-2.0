
#include "Character/EventCharacter.h"
#include "Character/Abilities/AbilityComponent_Base.h"


AEventCharacter::AEventCharacter()
{
	AbilityComponent = CreateDefaultSubobject<UAbilityComponent_Base>(TEXT("Ability Component"));
}
