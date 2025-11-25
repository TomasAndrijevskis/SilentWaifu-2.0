
#include "UI/Cards/LimitIncreaseCard.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "GameMode/Helpers/MoneyManager.h"
#include "UI/ConfirmationWindow.h"
#include "UI/WidgetReferenceDataAsset.h"
#include "UI/Screens/MainScreen.h"


void ULimitIncreaseCard::Init()
{
	Super::Init();
	OnCardCreatedDelegate.AddDynamic(this, &ULimitIncreaseCard::HandleCardState);
	if (!MoneyManager) return;
	MoneyManager->OnLimitLevelUpgradedDelegate.AddUniqueDynamic(this, &ULimitIncreaseCard::HandleCardState);
}


void ULimitIncreaseCard::CreateCard()
{
	Init();
	SetImage(Image_LimitIncreaseImage);
	OnCardCreatedDelegate.Broadcast();
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
	if (!WidgetReferences || !WidgetReferences->MainScreenRef) return;
	WidgetReferences->MainScreenRef->CreateConfirmationWindow();
	if (!WidgetReferences->ConfirmationWindowRef) return;
	WidgetReferences->ConfirmationWindowRef->OnSuccessDelegate.AddDynamic(this, &ULimitIncreaseCard::IncreaseLimit);
	WidgetReferences->ConfirmationWindowRef->SetPrice(Price);
}


void ULimitIncreaseCard::IncreaseLimit()
{
	if (!MoneyManager) return;
	MoneyManager->IncreaseMoneyLimit();
}


void ULimitIncreaseCard::HandleCardState()
{
	if (!MoneyManager) return;
	//UE_LOG(LogTemp, Warning, TEXT("Is level maxed: %i"), (MoneyManager->IsLimitLevelMaxed() ? 1 : 0));
	if (MoneyManager->IsLimitLevelMaxed())
	{
		SetPriceText("Maxed");
		Button_Action->SetIsEnabled(false);
	}
	else
	{
		Price = MoneyManager->GetLimitLevelUpgradePrice();
		SetPriceText(FString::FromInt(Price));
	}
}


void ULimitIncreaseCard::SetPriceText(const FString& NewPriceText)
{
	Text_Price->SetText(FText::FromString(NewPriceText));
}



