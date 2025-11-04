
#include "UI/Screens/CharacterInfoScreen.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "DataTables/CharacterData.h"
#include "GameMode/SilentWaifuGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "UI/WidgetReferenceDataAsset.h"


void UCharacterInfoScreen::NativeConstruct()
{
	Super::NativeConstruct();
	Button_Close->OnClicked.AddDynamic(this, &UCharacterInfoScreen::CloseScreen);
	Button_Upgrade->OnClicked.AddDynamic(this, &UCharacterInfoScreen::UpgradeCharacter);
	OnCharacterIdSetDelegate.AddDynamic(this, &UCharacterInfoScreen::SetCharacterInfo);
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
	SetName(CharacterRow->Name);
	SetImage(CharacterRow->Images.DefaultImage);
	for (const auto Character : GameMode->GetAvailableCharacters())
	{
		if (CharacterId == Character.Key)
		{
			SetLevel(Character.Value.Level);
			break;
		}
	}
	SetMoneyGain(CharacterRow->Numbers.CoinsPerLevel[CurrentLevel-1]);
	SetUpgradePrice(CharacterRow->Numbers.UpgradeCost[CurrentLevel-1]);
}


void UCharacterInfoScreen::GetCharacterInfo()
{
	if (!CharacterDataTable) return;
	const FName RowName = FName(*FString::FromInt(CharacterId));
	CharacterRow = CharacterDataTable->FindRow<FCharacterData>(RowName, TEXT("Find Character By Id"));
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
	UE_LOG(LogTemp, Display, TEXT("UpgradeCharacter"));
}


void UCharacterInfoScreen::SetImage(UTexture2D* NewImage)
{
	if (!NewImage) return;
	Image_Character->SetBrushFromTexture(NewImage);
}


void UCharacterInfoScreen::SetName(const FString& NewName)
{
	Text_CharacterName->SetText(FText::FromString(NewName));
}


void UCharacterInfoScreen::SetLevel(const int NewLevel)
{
	Text_LevelValue->SetText(FText::FromString(FString::FromInt(NewLevel)));
	CurrentLevel = NewLevel;
}


void UCharacterInfoScreen::SetMoneyGain(const int NewCoinsGain)
{
	Text_MoneyGainValue->SetText(FText::FromString(FString::FromInt(NewCoinsGain)));
}


void UCharacterInfoScreen::SetUpgradePrice(const int NewUpgradePrice)
{
	Text_UpgradePriceValue->SetText(FText::FromString(FString::FromInt(NewUpgradePrice)));
}
