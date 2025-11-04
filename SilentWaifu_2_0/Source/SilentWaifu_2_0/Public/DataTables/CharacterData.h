#pragma once

#include "CoreMinimal.h"
#include "CharacterValues.h"
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
	FString Name;
	
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* CardImage;

	UPROPERTY(EditDefaultsOnly)
	UTexture2D* MainScreenImage;

	UPROPERTY(EditDefaultsOnly)
	int Price;
	
	UPROPERTY(EditDefaultsOnly)
	FCharacterValues Values;
};
