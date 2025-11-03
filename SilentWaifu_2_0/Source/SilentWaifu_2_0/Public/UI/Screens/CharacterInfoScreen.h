
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterInfoScreen.generated.h"


class UWidgetReferenceDataAsset;
class UBorder;
class UTextBlock;
class UButton;
class UImage;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCharacterIdSetSignature);
UCLASS()
class SILENTWAIFU_2_0_API UCharacterInfoScreen : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	void SetCharacterId(const int NewCharacterId);

	FOnCharacterIdSetSignature OnCharacterIdSetDelegate;
	
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
	UTextBlock* Text_CoinsGainText;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Text_CoinsGainValue;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Text_CoinsGainDetails;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Text_UpgradePriceText;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Text_UpgradePriceValue;

	UFUNCTION()
	void CloseScreen();

	UFUNCTION()
	void UpgradeCharacter();

	void SetName(FString NewName);

	void SetLevel(int NewLevel);

	void SetCoins(int NewCoinsGain);

	void SetUpgradePrice(int NewUpgradePrice);

	UFUNCTION()
	void GetCharacterInfo();

	UPROPERTY(EditAnywhere)
	UDataTable* CharacterDataTable;
	
	int CharacterId;
};
