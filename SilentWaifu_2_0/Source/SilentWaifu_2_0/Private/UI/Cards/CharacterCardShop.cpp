
#include "UI/Cards/CharacterCardShop.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "DataTables/CharacterData.h"
#include "GameMode/Helpers/CharactersManager.h"
#include "UI/ConfirmationWindow.h"
#include "UI/WidgetReferenceDataAsset.h"
#include "UI/Screens/CharacterStatsScreen.h"
#include "UI/Screens/MainScreen.h"


void UCharacterCardShop::Init()
{
	Super::Init();
	OnCardCreatedDelegate.AddDynamic(this, &UCharacterCardShop::HandleState);
	OnCardCreatedDelegate.AddDynamic(this, &UCharacterCardShop::SetCharacterRow);
	OnCardCreatedDelegate.AddDynamic(this, &UCharacterCardShop::SetPriceText);
	OnCharacterUnlockedDelegate.AddDynamic(this, &UCharacterCardShop::HandleState);
	Button_AdditionalInfo->OnClicked.AddUniqueDynamic(this, &UCharacterCardShop::CreateAdditionalInfoScreen);
}


void UCharacterCardShop::SetImage(UTexture2D* NewImage)
{
	if (!NewImage) return;
	FButtonStyle Style;
	ApplyCardBrushStyle(Style.Normal, NewImage);
	ApplyCardBrushStyle(Style.Hovered, NewImage);
	ApplyCardBrushStyle(Style.Pressed, NewImage);
	ApplyCardBrushStyle(Style.Disabled, NewImage);
	Style.Disabled.TintColor = FSlateColor(FLinearColor(1.f, 1.f, 1.f, 0.2f)); 
	Button_CharacterImage->SetStyle(Style);
}


void UCharacterCardShop::ApplyCardBrushStyle(FSlateBrush& BrushStyle, UTexture2D* Image)
{
	BrushStyle.SetResourceObject(Image);
	BrushStyle.DrawAs = ESlateBrushDrawType::Image;
	BrushStyle.Tiling = ESlateBrushTileType::NoTile;
	BrushStyle.ImageSize = ImageSize;
}


void UCharacterCardShop::Action()
{
	if (!WidgetReferences || !WidgetReferences->MainScreenRef) return;
	WidgetReferences->MainScreenRef->CreateConfirmationWindow(false);
	if (!WidgetReferences->ConfirmationWindowRef) return;
	WidgetReferences->ConfirmationWindowRef->OnSuccessDelegate.AddDynamic(this, &UCharacterCardShop::UnlockCharacter);
	WidgetReferences->ConfirmationWindowRef->SetPrice(GetCharacterPrice());
}


void UCharacterCardShop::HandleState()
{
	if (!CharactersManager) return;
	Button_AdditionalInfo->SetIsEnabled(!CharactersManager->IsCharacterUnlocked(CharacterId));
	Button_Action->SetIsEnabled(!CharactersManager->IsCharacterUnlocked(CharacterId));
	Button_CharacterImage->SetIsEnabled(!CharactersManager->IsCharacterUnlocked(CharacterId));
}


void UCharacterCardShop::UnlockCharacter()
{
	if (!CharacterRow || !CharactersManager) return;
	FSavedCharactersData Data;
	Data.CharacterClass = CharacterRow->CharacterClass;
	Data.CharacterId = CharacterId;
	CharactersManager->OnCharacterAddedDelegate.Broadcast(CharacterId, Data);
	OnCharacterUnlockedDelegate.Broadcast();
}


void UCharacterCardShop::SetCharacterRow()
{
	if (!CharacterDataTable) return;
	const FName RowName = FName(*FString::FromInt(CharacterId));
	CharacterRow = CharacterDataTable->FindRow<FCharacterData>(RowName, TEXT("Find Character By Id"));
}


void UCharacterCardShop::SetPriceText()
{
	Text_Price->SetText(FText::FromString(FString::FromInt(GetCharacterPrice())));
}


void UCharacterCardShop::CreateAdditionalInfoScreen()
{
	if (!WidgetReferences || !WidgetReferences->CharacterStatsScreenClass) return;
	WidgetReferences->CharacterStatsScreenRef = Cast<UCharacterStatsScreen>(CreateWidget(GetWorld(), WidgetReferences->CharacterStatsScreenClass));
	if (!WidgetReferences->CharacterStatsScreenRef) return;
	WidgetReferences->CharacterStatsScreenRef->AddToViewport(5);
	WidgetReferences->CharacterStatsScreenRef->Init(CharacterRow);
}


int UCharacterCardShop::GetCharacterPrice() const
{
	if (!CharacterRow) return 0;
	return CharacterRow->Numbers.Price;
}
