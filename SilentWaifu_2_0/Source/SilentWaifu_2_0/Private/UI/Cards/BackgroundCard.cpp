
#include "UI/Cards/BackgroundCard.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "GameMode/SilentWaifuGameMode.h"
#include "GameMode/Helpers/BackgroundManager.h"
#include "UI/BackgroundOverviewWindow.h"
#include "UI/WidgetReferenceDataAsset.h"
#include "UI/Screens/MainScreen.h"


void UBackgroundCard::Init()
{
	Super::Init();
	if (!GameMode) return;
	BackgroundManager = GameMode->BackgroundManager;
}


void UBackgroundCard::CreateCard(UTexture2D* NewImage, int BackgroundId, int NewPrice)
{
	Init();
	Id = BackgroundId;
	Price = NewPrice;
	SetImage(NewImage);
}


bool UBackgroundCard::IsBackgroundUnlocked()
{
	if (!BackgroundManager) return false;
	TArray<FSavedBackgroundsData> SavedBackgrounds = BackgroundManager->GetUnlockedBackgrounds();
	if (SavedBackgrounds.Num() == 0) return false;
	for (const auto& Background : SavedBackgrounds)
	{
		if (Id == Background.Id) return true;
	}
	return false;
}


void UBackgroundCard::SetImage(UTexture2D* NewImage)
{
	if (!NewImage) return;
	Image = NewImage;
	FButtonStyle Style;
	ApplyCardBrushStyle(Style.Normal, NewImage);
	Style.Normal.TintColor = FSlateColor(FLinearColor(1.f, 1.f, 1.f, 1.f));
	ApplyCardBrushStyle(Style.Hovered, NewImage);
	Style.Normal.TintColor = FSlateColor(FLinearColor(.5f, .5f, .5f, 1.f));
	ApplyCardBrushStyle(Style.Pressed, NewImage);
	ApplyCardBrushStyle(Style.Disabled, NewImage);
	if (IsBackgroundUnlocked())
	{
		Border->SetBrushColor(FLinearColor(0.f, 1.f, 0, 1.f));
	}
	else
	{
		Border->SetBrushColor(FLinearColor(1.f, 0.f, 0, 1.f)),
		Style.Normal.TintColor = FSlateColor(FLinearColor(.3f, .3f, .3f, 1.f));
		Style.Hovered.TintColor = FSlateColor(FLinearColor(1.f, 1.f, 1.f, 1.f));
	}
	Button_Action->SetStyle(Style);
}


void UBackgroundCard::ApplyCardBrushStyle(FSlateBrush& BrushStyle, UTexture2D* CardImage)
{
	BrushStyle.SetResourceObject(CardImage);
	BrushStyle.DrawAs = ESlateBrushDrawType::Image;
	BrushStyle.Tiling = ESlateBrushTileType::NoTile;
	BrushStyle.ImageSize = ImageSize;
}


void UBackgroundCard::Action()
{
	if (!BackgroundManager || !WidgetReferences || !WidgetReferences->BackgroundOverviewWindowClass) return;
	WidgetReferences->BackgroundOverviewWindowRef = Cast<UBackgroundOverviewWindow>(CreateWidget(GetWorld(), WidgetReferences->BackgroundOverviewWindowClass));
	if (!WidgetReferences->BackgroundOverviewWindowRef) return;
	WidgetReferences->BackgroundOverviewWindowRef->AddToViewport(2);
	WidgetReferences->BackgroundOverviewWindowRef->Button_Close->OnClicked.AddUniqueDynamic(this, &UBackgroundCard::RemoveOverviewWindow);
	WidgetReferences->BackgroundOverviewWindowRef->Init(Image, Price, Id, IsBackgroundUnlocked(), BackgroundManager);
	WidgetReferences->MainScreenRef->OnBackgroundSetDelegate.AddUniqueDynamic(this, &UBackgroundCard::RemoveOverviewWindow);
}


void UBackgroundCard::RemoveOverviewWindow()
{
	if (!WidgetReferences->BackgroundOverviewWindowRef) return;
	WidgetReferences->BackgroundOverviewWindowRef->RemoveFromParent();
	WidgetReferences->BackgroundOverviewWindowRef = nullptr;
}
