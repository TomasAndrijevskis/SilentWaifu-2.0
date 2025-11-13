
#include "UI/Cards/BackgroundCard.h"
#include "Components/Button.h"
#include "GameMode/SilentWaifuGameMode.h"
#include "GameMode/Helpers/BackgroundManager.h"
#include "UI/BackgroundOverviewWindow.h"
#include "UI/WidgetReferenceDataAsset.h"


void UBackgroundCard::Init()
{
	Super::Init();
	if (!GameMode) return;
	BackgroundManager = GameMode->BackgroundManager;
}


void UBackgroundCard::CreateCard(UTexture2D* NewImage, int BackgroundId)
{
	Init();
	Id = BackgroundId;
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
	FButtonStyle CustomStyle;

	FSlateBrush NormalBrush;
	NormalBrush.SetResourceObject(NewImage);
	NormalBrush.DrawAs = ESlateBrushDrawType::Image;
	NormalBrush.Tiling = ESlateBrushTileType::NoTile;
	NormalBrush.ImageSize = ImageSize;
	
	FSlateBrush HoveredBrush;
	HoveredBrush.SetResourceObject(NewImage);
	HoveredBrush.DrawAs = ESlateBrushDrawType::Image;
	HoveredBrush.Tiling = ESlateBrushTileType::NoTile;
	HoveredBrush.ImageSize = ImageSize;

	IsBackgroundUnlocked() ?
		(NormalBrush.TintColor = FSlateColor(FLinearColor(0.f, 1.f, 0, 1.f)),
		HoveredBrush.TintColor = FSlateColor(FLinearColor(1.f, 1.f, 1.f, 1.f)))
	:
		(NormalBrush.TintColor = FSlateColor(FLinearColor(1.f, 0.f, 0.f, 1.f)),
		HoveredBrush.TintColor = FSlateColor(FLinearColor(1.f, 1.f, 1.f, 1.f)));

	CustomStyle.SetNormal(NormalBrush);
	CustomStyle.SetHovered(HoveredBrush);
	CustomStyle.SetDisabled(NormalBrush);
	CustomStyle.SetPressed(HoveredBrush);
	
	Button_Action->SetStyle(CustomStyle);
}


void UBackgroundCard::Action()
{
	if (!BackgroundManager || !WidgetReferences || !WidgetReferences->BackgroundOverviewWindowClass) return;
	WidgetReferences->BackgroundOverviewWindowRef = Cast<UBackgroundOverviewWindow>(CreateWidget(GetWorld(), WidgetReferences->BackgroundOverviewWindowClass));
	if (!WidgetReferences->BackgroundOverviewWindowRef) return;
	WidgetReferences->BackgroundOverviewWindowRef->AddToViewport(2);
	WidgetReferences->BackgroundOverviewWindowRef->Button_Close->OnClicked.AddDynamic(this, &UBackgroundCard::RemoveOverviewWindow);
	WidgetReferences->BackgroundOverviewWindowRef->Init(Image, 100, Id, IsBackgroundUnlocked(), BackgroundManager);
}


void UBackgroundCard::RemoveOverviewWindow()
{
	if (!WidgetReferences->BackgroundOverviewWindowRef) return;
	WidgetReferences->BackgroundOverviewWindowRef->RemoveFromParent();
	WidgetReferences->BackgroundOverviewWindowRef = nullptr;
}
