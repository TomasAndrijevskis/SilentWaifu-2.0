
#include "UI/Cards/LimitIncreaseCard.h"
#include "Components/Button.h"
#include "GameMode/SilentWaifuGameMode.h"


void ULimitIncreaseCard::SetImage(UTexture2D* NewImage)
{
	if (!Image_LimitIncreaseImage) return;
	
	FButtonStyle CustomStyle;
	// Normal Brush (Image)
	FSlateBrush NormalBrush;
	NormalBrush.SetResourceObject(Image_LimitIncreaseImage);
	NormalBrush.DrawAs = ESlateBrushDrawType::Image;
	NormalBrush.Tiling = ESlateBrushTileType::NoTile;
	NormalBrush.ImageSize = ImageSize;
	
	// Apply Brushes
	CustomStyle.SetNormal(NormalBrush);
	CustomStyle.SetHovered(NormalBrush);
	CustomStyle.SetDisabled(NormalBrush);
	CustomStyle.SetPressed(NormalBrush);
	
	Button_Image->SetStyle(CustomStyle);
}


void ULimitIncreaseCard::Action()
{
	if (!GameMode) return;
	GameMode->IncreaseMoneyLimit();
}
