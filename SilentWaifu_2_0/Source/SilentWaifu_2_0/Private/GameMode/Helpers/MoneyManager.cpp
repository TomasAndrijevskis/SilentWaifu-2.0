
#include "GameMode/Helpers/MoneyManager.h"


void UMoneyManager::Init(UDataTable* DataTable)
{
	if (!DataTable) return;
	MoneyLimitDataTable = DataTable;
}


void UMoneyManager::IncreaseMoney(const int Money)
{
	if (CurrentMoney + Money < MaxMoney)CurrentMoney += Money;
	else CurrentMoney = MaxMoney;
	OnCurrentMoneyChangedDelegate.Broadcast(CurrentMoney);
}


void UMoneyManager::DecreaseMoney(const int Money)
{
	CurrentMoney -= Money;
	OnCurrentMoneyChangedDelegate.Broadcast(CurrentMoney);
}


bool UMoneyManager::HasEnoughMoney(const int Money) const
{
	if (CurrentMoney >= Money) return true;
	return false;
}


void UMoneyManager::IncreaseMoneyLimit()
{
	MaxMoney += 200;
	OnMaxMoneyChangedDelegate.Broadcast(MaxMoney);
}


void UMoneyManager::SetMaxMoney(const int NewMaxMoney)
{
	MaxMoney = NewMaxMoney;
	OnMaxMoneyChangedDelegate.Broadcast(MaxMoney);
}
