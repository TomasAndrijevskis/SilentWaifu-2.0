
#include "UI/Cards/BackgroundCard.h"
#include "Components/Button.h"
#include "GameMode/SilentWaifuGameMode.h"
#include "GameMode/Helpers/BackgroundManager.h"


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


bool UBackgroundCard::HandleState()
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

	HandleState() ?
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
	if (!BackgroundManager) return;
	FSavedBackgroundsData Data;
	Data.Id = Id;
	Data.IsActive = true;
	BackgroundManager->AddUnlockedBackground(Data);
}

