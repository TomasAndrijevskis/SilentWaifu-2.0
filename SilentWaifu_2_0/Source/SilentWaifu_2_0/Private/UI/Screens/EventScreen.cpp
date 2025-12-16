
#include "UI/Screens/EventScreen.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "DataTables/CharacterData.h"
#include "GameMode/SilentWaifuGameMode.h"
#include "GameMode/Helpers/CharactersManager.h"
#include "GameMode/Helpers/EventsManager.h"
#include "GameMode/Helpers/MoneyManager.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGame/SavedCharactersData.h"
#include "UI/ConfirmationWindow.h"
#include "UI/WidgetReferenceDataAsset.h"
#include "UI/Screens/CharacterStatsScreen.h"
#include "UI/Screens/MainScreen.h"


void UEventScreen::NativeConstruct()
{
	Super::NativeConstruct();
	GameMode = Cast<ASilentWaifuGameMode>(UGameplayStatics::GetGameMode(this));
	if (!GameMode) return;
	SetEventEndDate(GameMode->GetEventEndTime());
	SetManagers();
	if (!MoneyManager || !CharactersManager || !EventsManager) return;
	BindDelegates();
	BindActions();
	SetEventMoneyText();
	SetExchangeRate();
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UEventScreen::CreateCountdown, 1, true, 0.f);
}


void UEventScreen::Init(const int NewCharacterId)
{
	if (!CharacterDataTable) return;
	CharacterId = NewCharacterId;
	const FName RowName = FName(*FString::FromInt(NewCharacterId));
	CharacterRow = CharacterDataTable->FindRow<FCharacterData>(RowName, TEXT("Find Character By Id"));
	OnCharacterDataLoadedDelegate.Broadcast();
}


void UEventScreen::SetManagers()
{
	MoneyManager = GameMode->MoneyManager;
	CharactersManager = GameMode->CharactersManager;
	EventsManager = GameMode->EventsManager;
}


void UEventScreen::BindDelegates()
{
	OnCharacterDataLoadedDelegate.AddUniqueDynamic(this, &UEventScreen::SetImage);
	OnCharacterDataLoadedDelegate.AddUniqueDynamic(this, &UEventScreen::SetPrice);
	OnCharacterDataLoadedDelegate.AddUniqueDynamic(this, &UEventScreen::HandleState);
	OnEventCharacterUnlockedDelegate.AddUniqueDynamic(this, &UEventScreen::HandleState);
	EventsManager->OnEventEndedDelegate.AddDynamic(this, &UEventScreen::CloseScreen);
	MoneyManager->OnEventMoneyChangedDelegate.AddUniqueDynamic(this, &UEventScreen::SetEventMoneyText);
}


void UEventScreen::BindActions()
{
	Slider_MoneyExchange->OnValueChanged.AddDynamic(this, &UEventScreen::SetExchangedMoney);
	Button_Close->OnClicked.AddDynamic(this, &UEventScreen::CloseScreen);
	Button_Exchange->OnClicked.AddDynamic(this, &UEventScreen::ExchangeMoney);
	Button_Action->OnClicked.AddDynamic(this, &UEventScreen::BuyCharacter);
	Button_Info->OnClicked.AddDynamic(this, &UEventScreen::CreateStatsScreen);
}


void UEventScreen::SetImage()
{
	if (!CharacterRow) return;
	Image_Character->SetBrushFromTexture(CharacterRow->Images.DefaultImage);
}


void UEventScreen::SetPrice()
{
	if (!CharacterRow) return;
	Price = CharacterRow->Numbers.Price;
	Text_PriceValue->SetText(FText::AsNumber(Price));
}


void UEventScreen::ExchangeMoney()
{
	if (!MoneyManager) return;
	int CurrentMoney = MoneyManager->GetCurrentMoney();
	int CoinsToExchange = Slider_MoneyExchange->GetValue() * CurrentMoney;
	if (CoinsToExchange == 0) return;
	MoneyManager->DecreaseMoney(CoinsToExchange);
	int CoinsForExchange = CoinsToExchange / ExchangeRate;
	MoneyManager->OnEventMoneyIncreasedDelegate.Broadcast(CoinsForExchange);
	Slider_MoneyExchange->SetValue(0);
}


void UEventScreen::SetEventMoneyText()
{
	if (!MoneyManager) return;
	Text_EventCoins->SetText(FText::AsNumber(MoneyManager->GetEventMoney()));
}


void UEventScreen::SetExchangeRate()
{
	FString RateText = "1: "+ FString::FromInt(ExchangeRate);
	Text_ExchangeRateValue->SetText(FText::FromString(RateText));
}


void UEventScreen::BuyCharacter()
{
	if (!WidgetReferences || !WidgetReferences->ConfirmationWindowClass || !CharacterRow) return;
	WidgetReferences->MainScreenRef->CreateConfirmationWindow(true);
	if (!WidgetReferences->ConfirmationWindowRef) return;
	WidgetReferences->ConfirmationWindowRef->OnSuccessDelegate.AddUniqueDynamic(this, &UEventScreen::UnlockEventCharacter);
	WidgetReferences->ConfirmationWindowRef->SetPrice(Price);
}


void UEventScreen::HandleState()
{
	if (!CharactersManager) return;
	Button_Action->SetIsEnabled(!CharactersManager->IsCharacterUnlocked(CharacterId));
}


void UEventScreen::UnlockEventCharacter()
{
	if (!CharacterRow || !CharactersManager) return;
	FSavedCharactersData Data;
	Data.CharacterClass = CharacterRow->CharacterClass;
	Data.bIsOnScreen = false;
	Data.CharacterId = CharacterId;
	Data.Level = 1;
	Data.TimeLeft = 60;
	CharactersManager->OnCharacterAddedDelegate.Broadcast(CharacterId, Data);
	OnEventCharacterUnlockedDelegate.Broadcast();
}


void UEventScreen::SetEventEndDate(const FDateTime& EndDate)
{
	EventEndTime = EndDate;
}


void UEventScreen::CreateCountdown()
{
	FTimespan TimeLeft = EventEndTime - FDateTime::Now();
	FString FormatedTime;
	if (TimeLeft.GetDays() == 0) FormatedTime = TimeLeft.ToString(TEXT("%h:%m:%s"));
	else FormatedTime = TimeLeft.ToString(TEXT("%d:%h:%m:%s"));
	if (FormatedTime.StartsWith(TEXT("+"))) FormatedTime.RemoveAt(0);
	Text_RemainingTime->SetText(FText::FromString(FormatedTime));
}


void UEventScreen::SetExchangedMoney(const float NewValue)
{
	if (!MoneyManager) return;
	int CurrentMoney = MoneyManager->GetCurrentMoney();
	int CoinsToExchange = NewValue * CurrentMoney;
	int CoinsForExchange = CoinsToExchange / ExchangeRate;
	Text_CoinsToExchange->SetText(FText::AsNumber(CoinsToExchange));
	Text_CoinsForExchange->SetText(FText::AsNumber(CoinsForExchange));
}


void UEventScreen::CreateStatsScreen()
{
	if (!WidgetReferences || !WidgetReferences->CharacterStatsScreenClass) return;
	WidgetReferences->CharacterStatsScreenRef = Cast<UCharacterStatsScreen>(CreateWidget(this, WidgetReferences->CharacterStatsScreenClass));
	if (!WidgetReferences->CharacterStatsScreenRef) return;
	WidgetReferences->CharacterStatsScreenRef->Init(CharacterRow);
	WidgetReferences->CharacterStatsScreenRef->AddToViewport(6);
}


void UEventScreen::CloseScreen()
{
	if (!WidgetReferences || !WidgetReferences->EventScreenRef) return;
	WidgetReferences->EventScreenRef->RemoveFromParent();
	WidgetReferences->EventScreenRef = nullptr;
}


