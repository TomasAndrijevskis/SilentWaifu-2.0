
#include "Character/EventCharacter.h"
#include "Character/Abilities/AbilityComponent_Base.h"
#include "Character/Abilities/AbilityComponent_Event.h"


AEventCharacter::AEventCharacter()
{
	AbilityComponent = CreateDefaultSubobject<UAbilityComponent_Event>(TEXT("Ability Component"));
}
