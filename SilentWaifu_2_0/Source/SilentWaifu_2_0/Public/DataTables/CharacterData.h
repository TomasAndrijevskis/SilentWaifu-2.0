#pragma once

#include "CoreMinimal.h"
#include "CharacterImages.h"
#include "CharacterValues.h"
#include "ERarities.h"
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
	TEnumAsByte<ERarities> Rarity;
	
	UPROPERTY(EditDefaultsOnly)
	FCharacterValues Numbers;

	UPROPERTY(EditDefaultsOnly)
	FCharacterImages Images;
};
