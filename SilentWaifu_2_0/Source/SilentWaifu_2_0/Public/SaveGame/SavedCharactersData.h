#pragma once

#include "CoreMinimal.h"
#include "SavedAbilityData.h"
#include "SavedCharactersData.generated.h"


class ACharacterTemplate;

USTRUCT(BlueprintType)
struct SILENTWAIFU_2_0_API FSavedCharactersData: public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY()
	int CharacterId;
	
	UPROPERTY()
	TSubclassOf<ACharacterTemplate> CharacterClass;

	UPROPERTY(Transient)
	ACharacterTemplate* SpawnedCharacter = nullptr;
	
	UPROPERTY()
	bool bIsOnScreen = false;

	UPROPERTY()
	int Position = INDEX_NONE;

	UPROPERTY()
	int Level = 1;

	UPROPERTY()
	int TimeLeft = 60;

	UPROPERTY()
	FSavedAbilityData AbilityData;
};
