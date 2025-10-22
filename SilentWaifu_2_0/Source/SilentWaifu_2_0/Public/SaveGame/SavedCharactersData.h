#pragma once

#include "CoreMinimal.h"
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

	UPROPERTY()
	bool bIsOnScreen;
};
