
#include "UI/Cards/BackgroundCard.h"
#include "Components/Button.h"


void UBackgroundCard::NativeConstruct()
{
	Super::NativeConstruct();
}


void UBackgroundCard::CreateCard(UTexture2D* NewImage)
{
	SetImage(NewImage);
}


void UBackgroundCard::SetImage(UTexture2D* NewImage)
{
	if (!NewImage) return;
	FButtonStyle CustomStyle;
	// Normal Brush (Image)
	FSlateBrush NormalBrush;
	NormalBrush.SetResourceObject(NewImage);
	NormalBrush.DrawAs = ESlateBrushDrawType::Image;
	NormalBrush.Tiling = ESlateBrushTileType::NoTile;
	NormalBrush.ImageSize = ImageSize;
	
	// Apply Brushes
	CustomStyle.SetNormal(NormalBrush);
	CustomStyle.SetHovered(NormalBrush);
	CustomStyle.SetDisabled(NormalBrush);
	CustomStyle.SetPressed(NormalBrush);
	
	Button_Action->SetStyle(CustomStyle);
}


void UBackgroundCard::Action()
{
	Super::Action();
}
