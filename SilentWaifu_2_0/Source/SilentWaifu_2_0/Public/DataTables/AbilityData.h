#pragma once

#include "CoreMinimal.h"
#include "AbilityData.generated.h"

USTRUCT(BlueprintType)
struct SILENTWAIFU_2_0_API FAbilityData: public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	FString Description;

	UPROPERTY(EditDefaultsOnly)
	UTexture2D* Icon;

	UPROPERTY(EditDefaultsOnly)
	int Cooldown;
};
