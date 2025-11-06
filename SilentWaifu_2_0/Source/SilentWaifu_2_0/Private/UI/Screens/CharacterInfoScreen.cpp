
#include "UI/Screens/CharacterInfoScreen.h"

#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "DataTables/CharacterData.h"
#include "DataTables/CharacterRarities.h"
#include "GameMode/SilentWaifuGameMode.h"
#include "GameMode/Helpers/MoneyManager.h"
#include "Kismet/GameplayStatics.h"
#include "UI/WidgetReferenceDataAsset.h"


void UCharacterInfoScreen::NativeConstruct()
{
	Super::NativeConstruct();
	Button_Close->OnClicked.AddDynamic(this, &UCharacterInfoScreen::CloseScreen);
	Button_Upgrade->OnClicked.AddDynamic(this, &UCharacterInfoScreen::UpgradeCharacter);
	OnCharacterIdSetDelegate.AddDynamic(this, &UCharacterInfoScreen::SetCharacterInfo);
	OnCharacterUpgradedDelegate.AddDynamic(this, &UCharacterInfoScreen::SetLevel);
	OnCharacterUpgradedDelegate.AddDynamic(this, &UCharacterInfoScreen::SetMoneyGain);
	OnCharacterUpgradedDelegate.AddDynamic(this, &UCharacterInfoScreen::SetUpgradePrice);
	OnCharacterUpgradedDelegate.AddDynamic(this, &UCharacterInfoScreen::HandleButtonState);
	GameMode = Cast<ASilentWaifuGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
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
	SetMoneyGain();
	SetUpgradePrice();
	SetMaxLevel();
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
	if (CurrentLevel == MaxLevel)
	{
		Button_Upgrade->SetIsEnabled(false);
		Text_Upgrade->SetText(FText::FromString("Maxed"));
	}
}


void UCharacterInfoScreen::CloseScreen()
{
	if (WidgetReferences && WidgetReferences->CharacterInfoScreenRef)
	{
		this->RemoveFromParent();
		WidgetReferences->CharacterInfoScreenRef = nullptr;
	}
}


void UCharacterInfoScreen::UpgradeCharacter()
{
	if (!GameMode || !GameMode->MoneyManager->HasEnoughMoney(CurrentUpgradePrice)) return;
	for (auto& Character : GameMode->GetAvailableCharacters())
	{
		if (CharacterId == Character.Key)
		{
			Character.Value.Level += 1;
			break;
		}
	}
	GameMode->MoneyManager->DecreaseMoney(CurrentUpgradePrice);
	OnCharacterUpgradedDelegate.Broadcast();
	GameMode->OnCharacterUpgradeDelegate.Broadcast(CharacterId);
	UE_LOG(LogTemp, Display, TEXT("CharacterInfoScreen::UpdateCharacter"));
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
}


void UCharacterInfoScreen::SetName()
{
	Text_CharacterName->SetText(FText::FromString(CharacterRow->Name));
}


void UCharacterInfoScreen::SetLevel()
{
	for (const auto& Character : GameMode->GetAvailableCharacters())
	{
		if (CharacterId == Character.Key)
		{
			CurrentLevel = Character.Value.Level;
			break;
		}
	}
	Text_LevelValue->SetText(FText::FromString(FString::FromInt(CurrentLevel)));
}


void UCharacterInfoScreen::SetMaxLevel()
{
	MaxLevel = CharacterRow->Numbers.UpgradeCost.Num();
	UE_LOG(LogTemp, Error, TEXT("MaxLevel: %i"), MaxLevel);
}


void UCharacterInfoScreen::SetMoneyGain()
{
	Text_MoneyGainValue->SetText(FText::FromString(FString::FromInt(CharacterRow->Numbers.CoinsPerLevel[CurrentLevel-1])));
}


void UCharacterInfoScreen::SetUpgradePrice()
{
	CurrentUpgradePrice = CharacterRow->Numbers.UpgradeCost[CurrentLevel-1];
	Text_UpgradePriceValue->SetText(FText::FromString(FString::FromInt(CurrentUpgradePrice)));
}
