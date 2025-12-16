
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DataTables/CharacterData.h"
#include "EventScreen.generated.h"


class UEventsManager;
class UCharactersManager;
class ASilentWaifuGameMode;
class UMoneyManager;
class UWidgetReferenceDataAsset;
class UTextBlock;
class USlider;
class UImage;
class UButton;


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCharacterDataLoadedSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEventCharacterUnlockedSignature);
UCLASS()
class SILENTWAIFU_2_0_API UEventScreen : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	void Init(const int NewCharacterId);
	
	FOnCharacterDataLoadedSignature OnCharacterDataLoadedDelegate;

	FOnEventCharacterUnlockedSignature OnEventCharacterUnlockedDelegate;
	
private:

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Close;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Exchange;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Action;
	
	UPROPERTY(meta = (BindWidget))
	UButton* Button_Info;
	
	UPROPERTY(meta = (BindWidget))
	UImage* Image_Character;
	
	UPROPERTY(meta = (BindWidget))
	USlider* Slider_MoneyExchange;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_RemainingTime;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_EventCoins;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_CoinsToExchange;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_CoinsForExchange;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_ExchangeRateValue;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_PriceValue;
	
	UFUNCTION()
	void CloseScreen();
	
	UFUNCTION()
	void SetExchangedMoney(const float NewValue);

	void BindActions();

	UFUNCTION()
	void SetImage();

	UFUNCTION()
	void SetPrice();
	
	UFUNCTION()
	void ExchangeMoney();

	UFUNCTION()
	void SetEventMoneyText();

	void SetExchangeRate();

	UFUNCTION()
	void UnlockEventCharacter();

	UFUNCTION()
	void CreateCountdown();

	UFUNCTION()
	void SetEventEndDate(const FDateTime& EndDate);

	UFUNCTION()
	void BuyCharacter();

	UFUNCTION()
	void HandleState();

	void SetManagers();

	void BindDelegates();

	UFUNCTION()
	void CreateStatsScreen();
	
	UPROPERTY()
	UMoneyManager* MoneyManager;

	UPROPERTY()
	UCharactersManager* CharactersManager;

	UPROPERTY()
	UEventsManager* EventsManager;
	
	UPROPERTY()
	ASilentWaifuGameMode* GameMode;

	UPROPERTY(EditAnywhere)
	int ExchangeRate = 6;
	
	UPROPERTY(EditAnywhere)
	UWidgetReferenceDataAsset* WidgetReferences;

	UPROPERTY(EditAnywhere)
	UDataTable* CharacterDataTable;

	FCharacterData* CharacterRow;

	int Price = 0;

	FDateTime EventEndTime;

	FTimerHandle TimerHandle;

	int CharacterId = 0;
};

