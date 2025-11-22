#pragma once

#include "CoreMinimal.h"
#include "MoneyLimitUpgradeData.generated.h"

class ACharacterTemplate;

USTRUCT(BlueprintType)
struct SILENTWAIFU_2_0_API FMoneyLimitUpgradeData: public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	int Level;
	
	UPROPERTY(EditDefaultsOnly)
	int UpgradePrice;

	UPROPERTY(EditDefaultsOnly)
	int AddToLimit;
};
