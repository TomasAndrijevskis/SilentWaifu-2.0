
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WidgetReferenceDataAsset.generated.h"

class UBackgroundCard;
class UBackgroundMenu;
class UConfirmationWindow;
class UCharacterInfoScreen;
class ULimitIncreaseCard;
class UCharacterCardShop;
class UCharacterMenuShop;
class UCharacterCardMainScreen;
class UButtonCreateChooseScreen;
class UCharacterCardStorage;
class UCharacterCardChoose;
class UCharacterMenuChooseCharacter;
class UCardBase;
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
	TSubclassOf<UCharacterMenuShop> ShopScreenClass;

	UPROPERTY()
	UCharacterMenuShop* ShopScreenRef;

	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCharacterInfoScreen> CharacterInfoScreenClass;

	UPROPERTY()
	UCharacterInfoScreen* CharacterInfoScreenRef;


	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCharacterCardMainScreen> CharacterCardMainScreenClass;

	UPROPERTY()
	UCharacterCardMainScreen* CharacterCardMainScreenRef;


	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UBackgroundMenu> BackgroundMenuClass;

	UPROPERTY()
	UBackgroundMenu* BackgroundMenuRef;


	

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCharacterCardChoose> ChooseCharacterCardClass;

	UPROPERTY()
	UCharacterCardChoose* ChooseCharacterCardRef;


	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCharacterCardStorage> StorageCharacterCardClass;

	UPROPERTY()
	UCardBase* StorageCharacterCardRef;


	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCharacterCardShop> ShopCharacterCardClass;

	UPROPERTY()
	UCharacterCardShop* ShopCharacterCardRef;

	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ULimitIncreaseCard> LimitIncreaseCardClass;

	UPROPERTY()
	ULimitIncreaseCard* LimitIncreaseCardRef;


	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UBackgroundCard> BackgroundCardClass;

	UPROPERTY()
	UBackgroundCard* BackgroundCardRef;


	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UButtonCreateChooseScreen> ButtonCreateChooseScreenClass;

	UPROPERTY()
	UButtonCreateChooseScreen* ButtonCreateChooseScreenRef;


	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UConfirmationWindow> ConfirmationWindowClass;

	UPROPERTY()
	UConfirmationWindow* ConfirmationWindowRef;

};
