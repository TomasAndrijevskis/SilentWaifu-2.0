
#include "UI/BackgroundOverviewWindow.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "GameMode/Helpers/BackgroundManager.h"


void UBackgroundOverviewWindow::Init(UTexture2D* NewImage, int NewPrice, int NewId, const bool IsUnlocked, UBackgroundManager* NewBackgroundManager)
{
	if (!NewImage || !NewBackgroundManager) return;
	SetInitialValues(NewId, NewPrice, NewBackgroundManager);
	SetImage(NewImage);
	HandleActionButton(IsUnlocked);
}


void UBackgroundOverviewWindow::SetInitialValues(int NewId, int NewPrice, UBackgroundManager* NewBackgroundManager)
{
	BackgroundManager = NewBackgroundManager;
	Id = NewId;
	Price = NewPrice;
}


void UBackgroundOverviewWindow::HandleActionButton(const bool IsUnlocked)
{
	Button_Action->OnClicked.Clear();
	IsUnlocked ?
		(Button_Action->OnClicked.AddDynamic(this, &UBackgroundOverviewWindow::SetBackground),
		SetButtonText("Set"))
	:
		(Button_Action->OnClicked.AddDynamic(this, &UBackgroundOverviewWindow::UnlockBackground),
		SetButtonText(FString::FromInt(Price)));
}


void UBackgroundOverviewWindow::SetImage(UTexture2D* NewImage)
{
	Image = NewImage;
	Image_Background->SetBrushFromTexture(Image);
}


void UBackgroundOverviewWindow::SetButtonText(const FString& Text)
{
	Text_ActionText->SetText(FText::FromString(Text));
}


void UBackgroundOverviewWindow::UnlockBackground()
{
	UE_LOG(LogTemp, Warning, TEXT("overview action - UnlockBackground"))
	FSavedBackgroundsData Data;
	Data.Id = Id;
	Data.IsActive = true;
	BackgroundManager->AddUnlockedBackground(Data);
}


void UBackgroundOverviewWindow::SetBackground()
{
	BackgroundManager->SetCurrentBackground(Image);
}



