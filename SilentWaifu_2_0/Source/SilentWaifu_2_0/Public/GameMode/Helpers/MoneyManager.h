
#pragma once

#include "CoreMinimal.h"
#include "MoneyManager.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCurrentMoneyChangedSignature, const int, Money);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxMoneyChangedSignature, const int, Money);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelIncreasedSignature, const int, Money);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLimitLevelUpgradedSignature);
UCLASS()
class SILENTWAIFU_2_0_API UMoneyManager : public UObject
{
	GENERATED_BODY()

public:

	void Init(UDataTable* DataTable);
	
	UFUNCTION()
	void IncreaseMoney(const int Money);

	void DecreaseMoney(const int Money);

	bool HasEnoughMoney(const int Money) const;

	UFUNCTION()
	void IncreaseMoneyLimit();

	void SetMaxMoney(const int NewMaxMoney);

	UFUNCTION()
	void SetMoneyLimitLevel(const int Level);

	int GetCurrentMoney() const;

	int GetMaxMoney() const;

	bool IsLimitLevelMaxed() const;

	int GetLimitLevelUpgradePrice() const;

	int GetNextAdditionToLimit();
	
	FOnCurrentMoneyChangedSignature OnCurrentMoneyChangedDelegate;

	FOnMaxMoneyChangedSignature OnMaxMoneyChangedDelegate;

	FOnLevelIncreasedSignature OnLevelIncreasedDelegate;

	FOnLimitLevelUpgradedSignature OnLimitLevelUpgradedDelegate;
	
private:

	void CalculateMaxMoney();
	
	UPROPERTY()
	int CurrentMoney = 0;

	UPROPERTY()
	int MaxMoney;

	UPROPERTY()
	UDataTable* MoneyLimitDataTable;

	UPROPERTY()
	int MoneyLimitLevel;

	int CurrentLimitLevelPrice;

	bool bIsLimitLevelMaxed = false;
};
