#pragma once

#include "CoreMinimal.h"
#include "CharacterData.generated.h"

class ACharacterTemplate;

USTRUCT(BlueprintType)
struct SILENTWAIFU_2_0_API FCharacterData: public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	int CharacterId;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ACharacterTemplate> CharacterClass;

	UPROPERTY(EditDefaultsOnly)
	UTexture2D* CardImage;

	UPROPERTY(EditDefaultsOnly)
	UTexture2D* MainScreenImage;

	UPROPERTY(EditDefaultsOnly)
	int Price;
	
};
