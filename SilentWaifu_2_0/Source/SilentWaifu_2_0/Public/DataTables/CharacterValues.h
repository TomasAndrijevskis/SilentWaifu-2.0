#pragma once

#include "CoreMinimal.h"
#include "CharacterValues.generated.h"

class ACharacterTemplate;

USTRUCT(BlueprintType)
struct SILENTWAIFU_2_0_API FCharacterValues: public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	TArray<int> CoinsPerLevel;
	
	UPROPERTY(EditDefaultsOnly)
	TArray<int> UpgradeCost;
};
