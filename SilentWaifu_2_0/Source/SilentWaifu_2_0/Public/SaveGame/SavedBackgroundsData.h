#pragma once

#include "CoreMinimal.h"
#include "SavedBackgroundsData.generated.h"

class ACharacterTemplate;

USTRUCT(BlueprintType)
struct SILENTWAIFU_2_0_API FSavedBackgroundsData: public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY()
	int Id;
	
	UPROPERTY()
	bool IsActive;
};
