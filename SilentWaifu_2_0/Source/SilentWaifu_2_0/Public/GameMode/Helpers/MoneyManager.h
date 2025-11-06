
#pragma once

#include "CoreMinimal.h"
#include "MoneyManager.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCurrentMoneyChangedSignature, const int, Money);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxMoneyChangedSignature, const int, Money);
UCLASS()
class SILENTWAIFU_2_0_API UMoneyManager : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION()
	void IncreaseMoney(const int Money);

	void DecreaseMoney(const int Money);

	bool HasEnoughMoney(const int Money) const;

	UFUNCTION()
	void IncreaseMoneyLimit();

	void SetMaxMoney(const int NewMaxMoney);
	
	FOnCurrentMoneyChangedSignature OnCurrentMoneyChangedDelegate;

	FOnMaxMoneyChangedSignature OnMaxMoneyChangedDelegate;

private:

	UPROPERTY()
	int CurrentMoney = 0;

	UPROPERTY()
	int MaxMoney;
};
