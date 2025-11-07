
#include "UI/Cards/CharacterCardStorage.h"
#include "Components/Button.h"
#include "UI/WidgetReferenceDataAsset.h"
#include "UI/Screens/CharacterInfoScreen.h"


void UCharacterCardStorage::SetImage(UTexture2D* NewImage)
{
	if (!NewImage) return;
	
	FButtonStyle CustomStyle;

	// Normal Brush (Image)
	FSlateBrush NormalBrush;
	NormalBrush.SetResourceObject(NewImage);
	NormalBrush.DrawAs = ESlateBrushDrawType::Image;
	NormalBrush.Tiling = ESlateBrushTileType::NoTile;
	NormalBrush.ImageSize = ImageSize;
	
	// Hovered Brush
	FSlateBrush HoveredBrush;
	HoveredBrush.SetResourceObject(NewImage);
	HoveredBrush.DrawAs = ESlateBrushDrawType::Image;
	HoveredBrush.Tiling = ESlateBrushTileType::NoTile;
	HoveredBrush.ImageSize = ImageSize;
	HoveredBrush.TintColor = FSlateColor(FLinearColor(1.f, 1.f, 1.f, 0.7f));
	
	// Disabled Brush
	FSlateBrush DisabledBrush;
	DisabledBrush.SetResourceObject(NewImage);
	DisabledBrush.DrawAs = ESlateBrushDrawType::Image;
	DisabledBrush.Tiling = ESlateBrushTileType::NoTile;
	DisabledBrush.ImageSize = ImageSize;
	DisabledBrush.TintColor = FSlateColor(FLinearColor(1.f, 1.f, 1.f, 0.3f)); 
	
	// Apply Brushes
	CustomStyle.SetNormal(NormalBrush);
	CustomStyle.SetHovered(HoveredBrush);
	CustomStyle.SetDisabled(DisabledBrush);
	CustomStyle.SetPressed(HoveredBrush);
	
	Button_Action->SetStyle(CustomStyle);
}

void UCharacterCardStorage::Action()
{
	if (!WidgetReferences || !WidgetReferences->CharacterInfoScreenClass) return;
	WidgetReferences->CharacterInfoScreenRef = Cast<UCharacterInfoScreen>(CreateWidget(GetWorld(), WidgetReferences->CharacterInfoScreenClass));
	if (!WidgetReferences->CharacterInfoScreenClass) return;
	WidgetReferences->CharacterInfoScreenRef->AddToViewport(2);
	WidgetReferences->CharacterInfoScreenRef->SetCharacterId(CharacterId);
	
}
