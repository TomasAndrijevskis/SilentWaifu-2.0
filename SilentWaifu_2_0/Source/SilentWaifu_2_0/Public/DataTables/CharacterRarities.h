#pragma once

#include "CoreMinimal.h"
#include "AbilityData.h"
#include "CharacterRarities.generated.h"


class ACharacterTemplate;

USTRUCT(BlueprintType)
struct SILENTWAIFU_2_0_API FCharacterRarities: public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	UTexture2D* RarityBorder;

	UPROPERTY(EditDefaultsOnly)
	int DropChance;

	UPROPERTY(EditDefaultsOnly)
	FAbilityData AbilityData;
};
