
#include "UI/Screens/CharacterInfoScreen.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "DataTables/CharacterData.h"
#include "DataTables/CharacterRarities.h"
#include "GameMode/SilentWaifuGameMode.h"
#include "GameMode/Helpers/CharactersManager.h"
#include "Kismet/GameplayStatics.h"
#include "UI/ConfirmationWindow.h"
#include "UI/WidgetReferenceDataAsset.h"
#include "UI/Screens/CharacterStatsScreen.h"
#include "UI/Screens/CharacterStoryLine.h"
#include "UI/Screens/MainScreen.h"


void UCharacterInfoScreen::NativeConstruct()
{
	Super::NativeConstruct();
	GameMode = Cast<ASilentWaifuGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!GameMode) return;
	CharactersManager = GameMode->CharactersManager;
	MoneyManager = GameMode->MoneyManager;
	BindButtons();
	BindDelegates();
}


void UCharacterInfoScreen::BindButtons()
{
	Button_Close->OnClicked.AddDynamic(this, &UCharacterInfoScreen::CloseScreen);
	Button_Upgrade->OnClicked.AddDynamic(this, &UCharacterInfoScreen::CreateConfirmationWindow);
	Button_CharacterInfo->OnClicked.AddDynamic(this, &UCharacterInfoScreen::CreateStorylineScreen);
	Button_StatsInfo->OnClicked.AddDynamic(this, &UCharacterInfoScreen::CreateStatsScreen);
}


void UCharacterInfoScreen::BindDelegates()
{
	OnCharacterIdSetDelegate.AddDynamic(this, &UCharacterInfoScreen::SetCharacterInfo);
	OnCharacterUpgradedDelegate.AddDynamic(this, &UCharacterInfoScreen::SetLevel);
	OnCharacterUpgradedDelegate.AddDynamic(this, &UCharacterInfoScreen::SetMoney);
	OnCharacterUpgradedDelegate.AddDynamic(this, &UCharacterInfoScreen::SetUpgradePrice);
	OnCharacterUpgradedDelegate.AddDynamic(this, &UCharacterInfoScreen::HandleButtonState);
}


void UCharacterInfoScreen::CreateStorylineScreen()
{
	if (!WidgetReferences || !WidgetReferences->CharacterStoryLineClass || !CharactersManager) return;
	WidgetReferences->CharacterStoryLineRef = Cast<UCharacterStoryLine>(CreateWidget(GetWorld(), WidgetReferences->CharacterStoryLineClass));
	if (!WidgetReferences->CharacterStoryLineRef) return;
	WidgetReferences->CharacterStoryLineRef->AddToViewport(5);
	WidgetReferences->CharacterStoryLineRef->Init(CharacterRow->Images.CardImage, CharacterRow->Name, CharacterRow->StoryLine);
	WidgetReferences->CharacterStoryLineRef->Button_Close->OnClicked.AddDynamic(this, &UCharacterInfoScreen::RemoveStorylineScreen);
}


void UCharacterInfoScreen::RemoveStorylineScreen()
{
	if (!WidgetReferences || !WidgetReferences->CharacterStoryLineRef) return;
	WidgetReferences->CharacterStoryLineRef->RemoveFromParent();
	WidgetReferences->CharacterStoryLineRef = nullptr;
}


void UCharacterInfoScreen::CreateStatsScreen()
{
	if (!WidgetReferences || !WidgetReferences->CharacterStatsScreenClass) return;
	WidgetReferences->CharacterStatsScreenRef = Cast<UCharacterStatsScreen>(CreateWidget(GetWorld(), WidgetReferences->CharacterStatsScreenClass));
	if (!WidgetReferences->CharacterStatsScreenRef) return;
	WidgetReferences->CharacterStatsScreenRef->Init(CharacterRow);
	WidgetReferences->CharacterStatsScreenRef->AddToViewport(5);
}


void UCharacterInfoScreen::SetCharacterId(const int NewCharacterId)
{
	CharacterId = NewCharacterId;
	OnCharacterIdSetDelegate.Broadcast();
}


void UCharacterInfoScreen::SetCharacterInfo()
{
	if (!GameMode) return;
	if (!CharacterRow) GetCharacterInfo();
	SetName();
	SetImage();
	SetRarityBorder();
	SetLevel();
	SetMoney();
	SetUpgradePrice();
	HandleButtonState();
}


void UCharacterInfoScreen::GetCharacterInfo()
{
	if (!CharacterDataTable) return;
	const FName RowName = FName(*FString::FromInt(CharacterId));
	CharacterRow = CharacterDataTable->FindRow<FCharacterData>(RowName, TEXT("Find Character By Id"));
}


void UCharacterInfoScreen::HandleButtonState()
{
	if (CurrentLevel == CharacterRow->Numbers.MaxLevel)
	{
		Button_Upgrade->SetIsEnabled(false);
		Text_Upgrade->SetText(FText::FromString("Maxed"));
	}
}


void UCharacterInfoScreen::CreateConfirmationWindow()
{
	if (!WidgetReferences || !WidgetReferences->MainScreenRef) return;
	WidgetReferences->MainScreenRef->CreateConfirmationWindow();
	if (!WidgetReferences->ConfirmationWindowRef) return;
	WidgetReferences->ConfirmationWindowRef->OnSuccessDelegate.AddDynamic(this, &UCharacterInfoScreen::UpgradeCharacter);
	WidgetReferences->ConfirmationWindowRef->SetPrice(CurrentUpgradePrice);
}


void UCharacterInfoScreen::CloseScreen()
{
	if (!WidgetReferences || !WidgetReferences->CharacterInfoScreenRef) return;
	this->RemoveFromParent();
	WidgetReferences->CharacterInfoScreenRef = nullptr;
}


void UCharacterInfoScreen::UpgradeCharacter()
{
	if (!CharactersManager) return;
	for (auto& Character : CharactersManager->GetAvailableCharacters())
	{
		if (CharacterId == Character.Key)
		{
			Character.Value.Level += 1;
			break;
		}
	}
	OnCharacterUpgradedDelegate.Broadcast();
	CharactersManager->OnCharacterUpgradeDelegate.Broadcast(CharacterId);
}


void UCharacterInfoScreen::SetImage()
{
	if (!CharacterRow->Images.DefaultImage) return;
	Image_Character->SetBrushFromTexture(CharacterRow->Images.DefaultImage);
}


void UCharacterInfoScreen::SetRarityBorder()
{
	if (!RarityDataTable) return;
	const FString RarityString = StaticEnum<ERarities>()->GetNameStringByValue(CharacterRow->Rarity);
	const FName RowName = FName(*RarityString);
	const FCharacterRarities* RarityRow = RarityDataTable->FindRow<FCharacterRarities>(RowName, TEXT("Find Character By rarity"));
	if (!RarityRow) return;
	Border_Rarity->SetBrushFromTexture(RarityRow->RarityBorder);
	Border_Rarity->SetBrushColor(FLinearColor(1.f, 1.f, 1.f, 1.f));
}


void UCharacterInfoScreen::SetName()
{
	Text_CharacterName->SetText(FText::FromString(CharacterRow->Name));
}


void UCharacterInfoScreen::SetLevel()
{
	if (!CharactersManager) return;
	for (const auto& Character : CharactersManager->GetAvailableCharacters())
	{
		if (CharacterId == Character.Key)
		{
			CurrentLevel = Character.Value.Level;
			break;
		}
	}
	Text_LevelValue->SetText(FText::FromString(FString::FromInt(CurrentLevel)));
}


void UCharacterInfoScreen::SetMoney()
{
	Text_MoneyGainValue->SetText(FText::FromString(FString::FromInt(CharacterRow->Numbers.CoinsPerLevel[CurrentLevel-1])));
}


void UCharacterInfoScreen::SetUpgradePrice()
{
	CurrentUpgradePrice = CharacterRow->Numbers.UpgradeCost[CurrentLevel-1];
	Text_UpgradePriceValue->SetText(FText::FromString(FString::FromInt(CurrentUpgradePrice)));
}
