
#include "Character/Abilities/AbilityComponent_VeryRare.h"
#include "Character/CharacterTemplate.h"
#include "GameMode/Helpers/MoneyManager.h"


void UAbilityComponent_VeryRare::Action()
{
	if (!MoneyManager || !CharacterRef) return;
	MoneyManager->IncreaseMoney(CharacterRef->GetMoneyPerHour() * 2);
}
