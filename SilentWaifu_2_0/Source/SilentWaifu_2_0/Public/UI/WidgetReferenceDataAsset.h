
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WidgetReferenceDataAsset.generated.h"

class UCharacterCardStorage;
class UCharacterCardChoose;
class UChooseCharacterScreen;
class UCharacterCardBase;
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
	TSubclassOf<UChooseCharacterScreen> ChooseScreenClass;
	
	UPROPERTY()
	UChooseCharacterScreen* ChooseScreenRef;
	

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCharacterCardChoose> ChooseCharacterCardClass;

	UPROPERTY()
	UCharacterCardChoose* ChooseCharacterCardRef;


	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCharacterCardStorage> StorageCharacterCardClass;

	UPROPERTY()
	UCharacterCardBase* StorageCharacterCardRef;
};
