#pragma once

#include "CoreMinimal.h"
#include "SavedAbilityData.generated.h"


USTRUCT(BlueprintType)
struct SILENTWAIFU_2_0_API FSavedAbilityData: public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY()
	bool WasAbilityUsed = false;
	
	UPROPERTY()
	FDateTime UsageTime;
};
