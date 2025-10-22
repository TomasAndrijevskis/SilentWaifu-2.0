
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WidgetReferenceDataAsset.generated.h"

class UStorageCharacterCard;
class UStorageScreen;

UCLASS(BlueprintType)
class SILENTWAIFU_2_0_API UWidgetReferenceDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UStorageScreen> StorageScreenClass;
	
	UPROPERTY()
	UStorageScreen* StorageScreenRef;

	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UStorageCharacterCard> StorageCharacterCardClass;

	UPROPERTY()
	UStorageCharacterCard* StorageCharacterCardRef;
};
