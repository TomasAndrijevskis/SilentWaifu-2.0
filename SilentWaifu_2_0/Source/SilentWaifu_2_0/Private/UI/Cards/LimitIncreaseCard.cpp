
#include "UI/Cards/LimitIncreaseCard.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "GameMode/SilentWaifuGameMode.h"
#include "GameMode/Helpers/MoneyManager.h"


void ULimitIncreaseCard::NativeConstruct()
{
	Super::NativeConstruct();
	OnCardCreatedDelegate.AddDynamic(this, &ULimitIncreaseCard::SetPriceText);
}


void ULimitIncreaseCard::SetImage(UTexture2D* NewImage)
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
	
	Button_Image->SetStyle(CustomStyle);
}


void ULimitIncreaseCard::Action()
{
	if (!GameMode) return;
	if (!GameMode->MoneyManager->HasEnoughMoney(Price)) return
	GameMode->MoneyManager->DecreaseMoney(Price);
	GameMode->MoneyManager->IncreaseMoneyLimit();
}


void ULimitIncreaseCard::SetPriceText()
{
	Text_Price->SetText(FText::FromString(FString::FromInt(Price)));
}
