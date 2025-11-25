
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DataTables/CharacterData.h"
#include "CharacterInfoScreen.generated.h"


class UBackgroundBlur;
class UCharactersManager;
class UMoneyManager;
class ASilentWaifuGameMode;
class UWidgetReferenceDataAsset;
class UBorder;
class UTextBlock;
class UButton;
class UImage;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCharacterIdSetSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCharacterUpgradedSignature);
UCLASS()
class SILENTWAIFU_2_0_API UCharacterInfoScreen : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	void SetCharacterId(const int NewCharacterId);

	FOnCharacterIdSetSignature OnCharacterIdSetDelegate;

	FOnCharacterUpgradedSignature OnCharacterUpgradedDelegate;
	
protected:

	UPROPERTY(EditAnywhere)
	UWidgetReferenceDataAsset* WidgetReferences;
	
private:

	UPROPERTY(meta = (BindWidget))
	UImage* Image_Character;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Upgrade;

	UPROPERTY(meta=(BindWidget))
	UButton* Button_Close;

	UPROPERTY(meta=(BindWidget))
	UBorder* Border_Background;

	UPROPERTY(meta=(BindWidget))
	UBorder* Border_Rarity;
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Text_CharacterName;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Text_LevelText;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Text_LevelValue;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Text_MoneyGainText;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Text_MoneyGainValue;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Text_MoneyGainDetails;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Text_UpgradePriceText;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Text_UpgradePriceValue;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Text_Upgrade;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_InputBlocker;

	UPROPERTY(meta=(BindWidget))
	UBackgroundBlur* Blur;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_StatsInfo;
	
	UPROPERTY(meta = (BindWidget))
	UButton* Button_CharacterInfo;
	
	UFUNCTION()
	void CloseScreen();

	UFUNCTION()
	void UpgradeCharacter();

	void SetImage();

	void SetRarityBorder();
	
	void SetName();

	UFUNCTION()
	void SetLevel();

	void SetMaxLevel();
	
	UFUNCTION()
	void SetMoneyGain();

	UFUNCTION()
	void SetUpgradePrice();

	UFUNCTION()
	void SetCharacterInfo();

	void GetCharacterInfo();

	UFUNCTION()
	void HandleButtonState();

	UFUNCTION()
	void CreateConfirmationWindow();
	
	void BindDelegates();

	UFUNCTION()
	void CreateStorylineScreen();

	UFUNCTION()
	void RemoveStorylineScreen();
	
	UPROPERTY(EditAnywhere)
	UDataTable* CharacterDataTable;

	UPROPERTY(EditAnywhere)
	UDataTable* RarityDataTable;
	
	UPROPERTY()
	ASilentWaifuGameMode* GameMode;

	UPROPERTY()
	UMoneyManager* MoneyManager;

	UPROPERTY()
	UCharactersManager* CharactersManager;
	
	int CharacterId;

	int CurrentLevel;

	int MaxLevel;

	int CurrentUpgradePrice;

	FCharacterData* CharacterRow;
};
