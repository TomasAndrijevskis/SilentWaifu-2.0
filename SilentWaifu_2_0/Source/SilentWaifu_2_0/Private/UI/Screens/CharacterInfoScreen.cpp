
#include "UI/Screens/CharacterInfoScreen.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "UI/WidgetReferenceDataAsset.h"


void UCharacterInfoScreen::NativeConstruct()
{
	Super::NativeConstruct();
	Button_Close->OnClicked.AddDynamic(this, &UCharacterInfoScreen::CloseScreen);
	Button_Upgrade->OnClicked.AddDynamic(this, &UCharacterInfoScreen::UpgradeCharacter);
	OnCharacterIdSetDelegate.AddDynamic(this, &UCharacterInfoScreen::GetCharacterInfo);
}


void UCharacterInfoScreen::SetCharacterId(const int NewCharacterId)
{
	CharacterId = NewCharacterId;
	OnCharacterIdSetDelegate.Broadcast();
}


void UCharacterInfoScreen::GetCharacterInfo()
{
	if (CharacterDataTable)
	{
		
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
	UE_LOG(LogTemp, Display, TEXT("UpgradeCharacter"));
}


void UCharacterInfoScreen::SetName(FString NewName)
{
	Text_CharacterName->SetText(FText::FromString(NewName));
}


void UCharacterInfoScreen::SetLevel(int NewLevel)
{
	Text_CharacterName->SetText(FText::FromString(FString::FromInt(NewLevel)));
}


void UCharacterInfoScreen::SetCoins(int NewCoinsGain)
{
	Text_CharacterName->SetText(FText::FromString(FString::FromInt(NewCoinsGain)));
}


void UCharacterInfoScreen::SetUpgradePrice(int NewUpgradePrice)
{
	Text_CharacterName->SetText(FText::FromString(FString::FromInt(NewUpgradePrice)));
}
