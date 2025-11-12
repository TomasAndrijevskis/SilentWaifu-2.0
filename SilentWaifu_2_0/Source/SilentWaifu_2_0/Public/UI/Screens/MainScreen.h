
#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetReferenceDataAsset.h"
#include "Blueprint/UserWidget.h"
#include "MainScreen.generated.h"

class UBackgroundManager;
class UImage;
class UMoneyManager;
class UCharactersManager;
class UVerticalBox;
class UBackgroundBlur;
class ASilentWaifuGameMode;
class UButton;
class UTextBlock;
class UHorizontalBox;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterRemovedSignature, const int, Position);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterSpawnedSignature, const int, Position);

UCLASS()
class SILENTWAIFU_2_0_API UMainScreen : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;

	UFUNCTION()
	void UpdateCurrentMoney(int const Money);

	UFUNCTION()
	void UpdateMaxMoney(int const Money);

	UFUNCTION()
	void CreateConfirmationWindow();

	UFUNCTION()
	void RemoveConfirmationWindow();

	FOnCharacterRemovedSignature OnCharacterRemovedDelegate;

	FOnCharacterSpawnedSignature OnCharacterSpawnedDelegate;;
	
protected:
	
	UPROPERTY(EditAnywhere)
	UWidgetReferenceDataAsset* WidgetReferences;

private:

	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* HorizontalBox_MoneyPanel;

	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* HorizontalBox_CharacterSlots;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* VerticalBox_Characters;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_CurrentMoney;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_MaxMoney;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Storage;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Shop;
	
	UPROPERTY(meta = (BindWidget))
	UButton* Button_BackgroundsMenu;
	
	UPROPERTY(meta = (BindWidget))
	UImage* Image_Background;

	void InitializeReferences();

	void BindDelegates();
	
	UFUNCTION()
	void CreateStorage();

	UFUNCTION()
	void RemoveStorage();

	UFUNCTION()
	void CreateShop();

	UFUNCTION()
	void RemoveShop();

	void CreateSlots();

	void FillSlots();
	
	UFUNCTION()
	void CreateBgMenu();

	UFUNCTION()
	void RemoveBgMenu();

	UFUNCTION()
	void SetBackground(UTexture2D* CurrentBackground);
	
	UButtonCreateChooseScreen* CreateButton(const int SpawnPosition) const;

	UCharacterCardMainScreen* CreateCharacterCard(const int SpawnPosition) const;

	UFUNCTION()
	void RemoveButton(const int Position);

	UFUNCTION()
	void RemoveCharacter(const int Position);
	
	UPROPERTY()
	ASilentWaifuGameMode* GameMode;

	UPROPERTY()
	UCharactersManager* CharactersManager;

	UPROPERTY()
	UMoneyManager* MoneyManager;

	UPROPERTY()
	UBackgroundManager* BackgroundManager;
	
	int AmountOfSlots = 5;
};

