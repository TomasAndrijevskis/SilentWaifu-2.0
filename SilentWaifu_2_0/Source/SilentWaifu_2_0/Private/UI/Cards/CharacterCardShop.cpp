
#include "UI/Cards/CharacterCardShop.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "DataTables/CharacterData.h"
#include "GameMode/Helpers/CharactersManager.h"
#include "GameMode/Helpers/MoneyManager.h"
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

	FButtonStyle CustomStyle;
	// Normal Brush (Image)
	FSlateBrush NormalBrush;
	NormalBrush.SetResourceObject(NewImage);
	NormalBrush.DrawAs = ESlateBrushDrawType::Image;
	NormalBrush.Tiling = ESlateBrushTileType::NoTile;
	NormalBrush.ImageSize = ImageSize;
	
	// Disabled Brush
	FSlateBrush DisabledBrush;
	DisabledBrush.SetResourceObject(NewImage);
	DisabledBrush.DrawAs = ESlateBrushDrawType::Image;
	DisabledBrush.Tiling = ESlateBrushTileType::NoTile;
	DisabledBrush.ImageSize = ImageSize;
	DisabledBrush.TintColor = FSlateColor(FLinearColor(1.f, 1.f, 1.f, 0.3f)); 
	
	// Apply Brushes
	CustomStyle.SetNormal(NormalBrush);
	CustomStyle.SetHovered(NormalBrush);
	CustomStyle.SetDisabled(DisabledBrush);
	CustomStyle.SetPressed(NormalBrush);
	
	Button_CharacterImage->SetStyle(CustomStyle);
}


void UCharacterCardShop::Action()
{
	if (!WidgetReferences || !WidgetReferences->MainScreenRef) return;
	WidgetReferences->MainScreenRef->CreateConfirmationWindow();
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
	Data.bIsOnScreen = false;
	Data.CharacterId = CharacterId;
	Data.Level = 1;
	Data.TimeLeft = 10;
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
