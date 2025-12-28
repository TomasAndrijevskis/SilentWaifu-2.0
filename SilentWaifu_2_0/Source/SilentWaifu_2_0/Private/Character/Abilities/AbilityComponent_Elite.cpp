
#include "Character/Abilities/AbilityComponent_Elite.h"
#include "GameMode/Helpers/MoneyManager.h"


void UAbilityComponent_Elite::Action()
{
	if (!MoneyManager) return;
	const int CurrentMoney = MoneyManager->GetCurrentMoney();
	if (CurrentMoney == 0) return;
	const int RoundedMoney = RoundDigits(CurrentMoney);
	MoneyManager->IncreaseMoney(RoundedMoney - MoneyManager->GetCurrentMoney());
}


int UAbilityComponent_Elite::RoundDigits(const int CurrentMoney) const
{
	int DigitCount = 0;
	int Temp = CurrentMoney;
	while (Temp > 0)
	{
		Temp /= 10;
		++DigitCount;
	}
	int DigitsToClear = FMath::Min(6, DigitCount - 1);
	int Magnitude = 1;
	for (int i = 0; i < DigitsToClear; ++i)
	{
		Magnitude *= 10;
	}
	return ((CurrentMoney + Magnitude - 1) / Magnitude) * Magnitude;
}
