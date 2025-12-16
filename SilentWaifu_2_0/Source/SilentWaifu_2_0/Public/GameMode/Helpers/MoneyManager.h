
#pragma once

#include "CoreMinimal.h"
#include "MoneyManager.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCurrentMoneyChangedSignature, const int, Money);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxMoneyChangedSignature, const int, Money);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelIncreasedSignature, const int, Money);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLimitLevelUpgradedSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEventMoneyIncreasedSignature, int, Money);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEventMoneyDecreasedSignature, int, Money);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEventMoneyChangedSignature);
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

	bool HasEnoughEventMoney(const int Money) const;
	
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

	void SetEventMoney(const int Money);
	
	int GetEventMoney() const;

	UFUNCTION()
	void IncreaseEventMoney(const int Money);

	UFUNCTION()
	void DecreaseEventMoney(const int Money);

	UFUNCTION()
	void EraseEventMoney();
	
	FOnCurrentMoneyChangedSignature OnCurrentMoneyChangedDelegate;

	FOnMaxMoneyChangedSignature OnMaxMoneyChangedDelegate;

	FOnLevelIncreasedSignature OnLevelIncreasedDelegate;

	FOnLimitLevelUpgradedSignature OnLimitLevelUpgradedDelegate;

	FOnEventMoneyChangedSignature OnEventMoneyChangedDelegate;

	FOnEventMoneyIncreasedSignature OnEventMoneyIncreasedDelegate;

	FOnEventMoneyDecreasedSignature OnEventMoneyDecreasedDelegate;
	
private:

	void CalculateMaxMoney();
	
	UPROPERTY()
	int CurrentMoney = 0;
	
	UPROPERTY()
	int MaxMoney;

	UPROPERTY()
	int EventMoney = 0;
	
	UPROPERTY()
	UDataTable* MoneyLimitDataTable;

	UPROPERTY()
	int MoneyLimitLevel;

	int CurrentLimitLevelPrice;

	bool bIsLimitLevelMaxed = false;
};
