
#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetReferenceDataAsset.h"
#include "Blueprint/UserWidget.h"
#include "MainScreen.generated.h"

class UEventsManager;
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
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBackgroundSetSignature);
UCLASS()
class SILENTWAIFU_2_0_API UMainScreen : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;
	
	UFUNCTION()
	void CreateConfirmationWindow(bool IsEvent);

	UFUNCTION()
	void RemoveConfirmationWindow();
	
	FOnCharacterRemovedSignature OnCharacterRemovedDelegate;

	FOnCharacterSpawnedSignature OnCharacterSpawnedDelegate;;

	FOnBackgroundSetSignature OnBackgroundSetDelegate;
	
protected:
	
	UPROPERTY(EditAnywhere)
	UWidgetReferenceDataAsset* WidgetReferences;

private:
	
	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* HorizontalBox_CharacterSlots;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* VerticalBox_Characters;
	
	UPROPERTY(meta = (BindWidget))
	UButton* Button_Storage;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Shop;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Settings;
	
	UPROPERTY(meta = (BindWidget))
	UButton* Button_BackgroundsMenu;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Event;
	
	UPROPERTY(meta = (BindWidget))
	UImage* Image_Background;

	void InitializeReferences();

	void BindDelegates();
	
	UFUNCTION()
	void CreateStorage();

	UFUNCTION()
	void CreateShop();

	void CreateSlots();

	void FillSlots();
	
	UFUNCTION()
	void CreateBgMenu();

	UFUNCTION()
	void CreateSettings();
	
	UFUNCTION()
	void SetBackground(UTexture2D* CurrentBackground);

	UFUNCTION()
	void CreateEventScreen();
	
	UButtonCreateChooseScreen* CreateButton(const int SpawnPosition) const;

	UCharacterCardMainScreen* CreateCharacterCard(const int SpawnPosition) const;

	UFUNCTION()
	void RemoveButton(const int Position);

	UFUNCTION()
	void RemoveCharacter(const int Position);

	void CreateMoneyPanel();

	UFUNCTION()
	void HandleEvent(const bool HasEventStarted);
	
	UPROPERTY()
	ASilentWaifuGameMode* GameMode;

	UPROPERTY()
	UCharactersManager* CharactersManager;

	UPROPERTY()
	UMoneyManager* MoneyManager;

	UPROPERTY()
	UBackgroundManager* BackgroundManager;

	UPROPERTY()
	UEventsManager* EventsManager;
	
	int AmountOfSlots = 5;
};

