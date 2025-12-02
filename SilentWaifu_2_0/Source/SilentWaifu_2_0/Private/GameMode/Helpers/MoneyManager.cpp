
#include "GameMode/Helpers/MoneyManager.h"
#include "DataTables/MoneyLimitUpgradeData.h"


void UMoneyManager::Init(UDataTable* DataTable)
{
	if (!DataTable) return;
	MoneyLimitDataTable = DataTable;
	OnLevelIncreasedDelegate.AddDynamic(this, &UMoneyManager::SetMoneyLimitLevel);
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


void UMoneyManager::IncreaseMoneyLimit()
{
	MoneyLimitLevel++;
	//UE_LOG(LogTemp, Warning, TEXT("MaxMoney: %i"), MaxMoney);
	OnLevelIncreasedDelegate.Broadcast(MoneyLimitLevel);
}


void UMoneyManager::SetMaxMoney(const int NewMaxMoney)
{
	MaxMoney = NewMaxMoney;
	/*UE_LOG(LogTemp, Error, TEXT("MaxMoney: %i"), MaxMoney);
	UE_LOG(LogTemp, Error, TEXT("Level: %i"), MoneyLimitLevel);
	UE_LOG(LogTemp, Error, TEXT("upgrade price: %i"), GetLimitLevelUpgradePrice());*/
	OnLimitLevelUpgradedDelegate.Broadcast();
	OnMaxMoneyChangedDelegate.Broadcast(MaxMoney);
}


void UMoneyManager::SetMoneyLimitLevel(const int Level)
{
	MoneyLimitLevel = Level;
	//UE_LOG(LogTemp, Warning, TEXT("Level: %i"), MoneyLimitLevel);
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
	

