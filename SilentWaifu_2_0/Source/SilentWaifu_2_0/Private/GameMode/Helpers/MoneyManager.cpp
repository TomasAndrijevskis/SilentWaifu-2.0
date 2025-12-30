
#include "GameMode/Helpers/MoneyManager.h"
#include "DataTables/MoneyLimitUpgradeData.h"


void UMoneyManager::Init(UDataTable* DataTable)
{
	if (!DataTable) return;
	MoneyLimitDataTable = DataTable;
	OnLevelIncreasedDelegate.AddUniqueDynamic(this, &UMoneyManager::SetMoneyLimitLevel);
	OnEventMoneyIncreasedDelegate.AddUniqueDynamic(this, &UMoneyManager::IncreaseEventMoney);
	OnEventMoneyDecreasedDelegate.AddUniqueDynamic(this, &UMoneyManager::DecreaseEventMoney);
}


void UMoneyManager::IncreaseMoney(const int Money)
{
	if (CurrentMoney + Money < MaxMoney) CurrentMoney += Money;
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


bool UMoneyManager::HasEnoughEventMoney(const int Money) const
{
	if (EventMoney >= Money) return true;
	return false;
}


void UMoneyManager::IncreaseMoneyLimit()
{
	MoneyLimitLevel++;
	OnLevelIncreasedDelegate.Broadcast(MoneyLimitLevel);
}


void UMoneyManager::SetMaxMoney(const int NewMaxMoney)
{
	MaxMoney = NewMaxMoney;
	OnLimitLevelUpgradedDelegate.Broadcast();
	OnMaxMoneyChangedDelegate.Broadcast(MaxMoney);
}


void UMoneyManager::SetMoneyLimitLevel(const int Level)
{
	MoneyLimitLevel = Level;
	CalculateMaxMoney();
}


void UMoneyManager::CalculateMaxMoney()
{
	if (!MoneyLimitDataTable) return;
	TArray<FMoneyLimitUpgradeData*> Levels;
	MoneyLimitDataTable->GetAllRows(TEXT("Find Levels"), Levels);
	if (Levels.Num() == 0) return;
	MaxMoney = 0;
	int LevelGroupIndex = 0;
	int NewMaxMoney = 0;
	int PreviousGroupLevel = 0;
	int MaxLevel = Levels.Last()->Level;
	int TempLevel = 1;
	for (const auto LevelData : Levels)
	{
		CurrentLimitLevelPrice = LevelData->UpgradePrice;
		if (LevelGroupIndex != 0)
		{
			PreviousGroupLevel = Levels[LevelGroupIndex-1]->Level;
		}
		for (int j = 1; j <= LevelData->Level - PreviousGroupLevel; j++)
		{
			if (MoneyLimitLevel > LevelData->Level)
			{
				NewMaxMoney += LevelData->AddToLimit;
			}
			else if (TempLevel == MaxLevel)
			{
				NewMaxMoney += LevelData->AddToLimit;
				bIsLimitLevelMaxed = true;
				SetMaxMoney(NewMaxMoney);
				return;
			}
			else
			{
				if (j == MoneyLimitLevel - PreviousGroupLevel)
				{
					NewMaxMoney += LevelData->AddToLimit;
					SetMaxMoney(NewMaxMoney);
					return;
				}
				NewMaxMoney += LevelData->AddToLimit;
			}
			TempLevel++;
		}
		LevelGroupIndex++;
	}
}


int UMoneyManager::GetCurrentMoney() const
{
	return CurrentMoney;
}


int UMoneyManager::GetMaxMoney() const
{
	return MaxMoney;
}


bool UMoneyManager::IsLimitLevelMaxed() const
{
	return bIsLimitLevelMaxed;
}


int UMoneyManager::GetLimitLevelUpgradePrice() const
{
	return CurrentLimitLevelPrice;
}


int UMoneyManager::GetNextAdditionToLimit()
{
	if (!MoneyLimitDataTable) return 0;
	TArray<FMoneyLimitUpgradeData*> Levels;
	MoneyLimitDataTable->GetAllRows(TEXT("Find Levels"), Levels);
	if (Levels.Num() == 0) return 0;
	int LevelGroupIndex = 0;
	int PreviousGroupLevel = 0;
	for (const auto LevelData : Levels)
	{
		if (LevelGroupIndex != 0)
		{
			PreviousGroupLevel = Levels[LevelGroupIndex-1]->Level;
		}
		for (int j = 1; j <= LevelData->Level - PreviousGroupLevel; j++)
		{
			if (j == 1 + MoneyLimitLevel - PreviousGroupLevel)
			{
				return LevelData->AddToLimit;
			}
		}
		LevelGroupIndex++;
	}
	return 0;
}


void UMoneyManager::SetEventMoney(const int Money)
{
	EventMoney = Money;
}


int UMoneyManager::GetEventMoney() const
{
	return EventMoney;
}


void UMoneyManager::IncreaseEventMoney(const int Money)
{
	EventMoney += Money;
	OnEventMoneyChangedDelegate.Broadcast();
}


void UMoneyManager::DecreaseEventMoney(const int Money)
{
	EventMoney -= Money;
	OnEventMoneyChangedDelegate.Broadcast();
}


void UMoneyManager::EraseEventMoney()
{
	DecreaseEventMoney(EventMoney);
}
