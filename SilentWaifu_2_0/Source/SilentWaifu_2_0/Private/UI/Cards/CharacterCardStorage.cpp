
#include "UI/Cards/CharacterCardStorage.h"
#include "Components/Button.h"
#include "UI/WidgetReferenceDataAsset.h"
#include "UI/Screens/CharacterInfoScreen.h"


void UCharacterCardStorage::SetImage(UTexture2D* NewImage)
{
	if (!NewImage) return;
	FButtonStyle Style;
	ApplyCardBrushStyle(Style.Normal, NewImage);
	ApplyCardBrushStyle(Style.Hovered, NewImage);
	Style.Hovered.TintColor = FSlateColor(FLinearColor(1.f, 1.f, 1.f, 0.8f)); 
	ApplyCardBrushStyle(Style.Pressed, NewImage);
	Style.Pressed.TintColor = FSlateColor(FLinearColor(1.f, 1.f, 1.f, 0.5f));
	ApplyCardBrushStyle(Style.Disabled, NewImage);
	Style.Disabled.TintColor = FSlateColor(FLinearColor(1.f, 1.f, 1.f, 0.2f));
	Button_Action->SetStyle(Style);
}


void UCharacterCardStorage::ApplyCardBrushStyle(FSlateBrush& BrushStyle, UTexture2D* Image)
{
	BrushStyle.SetResourceObject(Image);
	BrushStyle.DrawAs = ESlateBrushDrawType::Image;
	BrushStyle.Tiling = ESlateBrushTileType::NoTile;
	BrushStyle.ImageSize = ImageSize;
}


void UCharacterCardStorage::Action()
{
	if (!WidgetReferences || !WidgetReferences->CharacterInfoScreenClass) return;
	WidgetReferences->CharacterInfoScreenRef = Cast<UCharacterInfoScreen>(CreateWidget(GetWorld(), WidgetReferences->CharacterInfoScreenClass));
	if (!WidgetReferences->CharacterInfoScreenClass) return;
	WidgetReferences->CharacterInfoScreenRef->AddToViewport(2);
	WidgetReferences->CharacterInfoScreenRef->SetCharacterId(CharacterId);
}
