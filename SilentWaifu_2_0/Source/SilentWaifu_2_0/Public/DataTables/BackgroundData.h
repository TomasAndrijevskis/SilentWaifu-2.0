#pragma once

#include "CoreMinimal.h"
#include "BackgroundData.generated.h"

class ACharacterTemplate;

USTRUCT(BlueprintType)
struct SILENTWAIFU_2_0_API FBackgroundData: public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	int Price;
	
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* Image;
};
