
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WidgetReferenceDataAsset.generated.h"

class UButtonCreateChooseScreen;
class UCharacterCardStorage;
class UCharacterCardChoose;
class UCharacterMenuChooseCharacter;
class UCharacterCardBase;
class UCharacterMenuStorage;
class UMainScreen;

UCLASS(BlueprintType)
class SILENTWAIFU_2_0_API UWidgetReferenceDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMainScreen> MainScreenClass;
	
	UPROPERTY()
	UMainScreen* MainScreenRef;

	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCharacterMenuStorage> StorageScreenClass;
	
	UPROPERTY()
	UCharacterMenuStorage* StorageScreenRef;


	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCharacterMenuChooseCharacter> ChooseScreenClass;
	
	UPROPERTY()
	UCharacterMenuChooseCharacter* ChooseScreenRef;
	

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCharacterCardChoose> ChooseCharacterCardClass;

	UPROPERTY()
	UCharacterCardChoose* ChooseCharacterCardRef;


	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCharacterCardStorage> StorageCharacterCardClass;

	UPROPERTY()
	UCharacterCardBase* StorageCharacterCardRef;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UButtonCreateChooseScreen> ButtonCreateChooseScreenClass;

	UPROPERTY()
	UButtonCreateChooseScreen* ButtonCreateChooseScreenRef;

};
