
#include "UI/Cards/LimitIncreaseCard.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "GameMode/Helpers/MoneyManager.h"
#include "UI/ConfirmationWindow.h"
#include "UI/LimitCardAdditionalInfo.h"
#include "UI/WidgetReferenceDataAsset.h"
#include "UI/Screens/MainScreen.h"


void ULimitIncreaseCard::Init()
{
	Super::Init();
	OnCardCreatedDelegate.AddDynamic(this, &ULimitIncreaseCard::HandleCardState);
	Button_AdditionalInfo->OnClicked.AddUniqueDynamic(this, &ULimitIncreaseCard::OpenAdditionalInfo);
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
	FButtonStyle Style;
	ApplyCardBrushStyle(Style.Normal, NewImage);
	ApplyCardBrushStyle(Style.Hovered, NewImage);
	ApplyCardBrushStyle(Style.Pressed, NewImage);
	ApplyCardBrushStyle(Style.Disabled, NewImage);
	Style.Disabled.TintColor = FSlateColor(FLinearColor(1.f, 1.f, 1.f, 0.2f)); 
	Button_Image->SetStyle(Style);
}


void ULimitIncreaseCard::ApplyCardBrushStyle(FSlateBrush& BrushStyle, UTexture2D* Image)
{
	BrushStyle.SetResourceObject(Image);
	BrushStyle.DrawAs = ESlateBrushDrawType::Image;
	BrushStyle.Tiling = ESlateBrushTileType::NoTile;
	BrushStyle.ImageSize = ImageSize;
}


void ULimitIncreaseCard::Action()
{
	if (!WidgetReferences || !WidgetReferences->MainScreenRef) return;
	WidgetReferences->MainScreenRef->CreateConfirmationWindow(false);
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
		Button_AdditionalInfo->SetIsEnabled(false);
	}
	else
	{
		Price = MoneyManager->GetLimitLevelUpgradePrice();
		SetPriceText(FString::FromInt(Price));
	}
}


void ULimitIncreaseCard::OpenAdditionalInfo()
{
	if (!WidgetReferences || !WidgetReferences->LimitCardAdditionalInfoClass || !MoneyManager) return;
	WidgetReferences->LimitCardAdditionalInfoRef = Cast<ULimitCardAdditionalInfo>(CreateWidget(GetWorld(), WidgetReferences->LimitCardAdditionalInfoClass));
	if (!WidgetReferences->LimitCardAdditionalInfoRef) return;
	WidgetReferences->LimitCardAdditionalInfoRef->AddToViewport(5);
	WidgetReferences->LimitCardAdditionalInfoRef->SetText(MoneyManager->GetNextAdditionToLimit());
	WidgetReferences->LimitCardAdditionalInfoRef->Button_Close->OnClicked.AddDynamic(this, &ULimitIncreaseCard::CloseAdditionalInfo);
}


void ULimitIncreaseCard::CloseAdditionalInfo()
{
	if (!WidgetReferences || !WidgetReferences->LimitCardAdditionalInfoRef) return;
	WidgetReferences->LimitCardAdditionalInfoRef->RemoveFromParent();
	WidgetReferences->LimitCardAdditionalInfoRef = nullptr;
}


void ULimitIncreaseCard::SetPriceText(const FString& NewPriceText)
{
	Text_Price->SetText(FText::FromString(NewPriceText));
}



