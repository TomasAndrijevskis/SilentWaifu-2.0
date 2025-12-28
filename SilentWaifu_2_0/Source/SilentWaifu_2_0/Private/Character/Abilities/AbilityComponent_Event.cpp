
#include "Character/Abilities/AbilityComponent_Event.h"
#include "GameMode/Helpers/MoneyManager.h"


void UAbilityComponent_Event::Action()
{
	if (!MoneyManager) return;
	const int CurrentMoney = MoneyManager->GetCurrentMoney();
	MoneyManager->IncreaseMoney(CurrentMoney);
}
