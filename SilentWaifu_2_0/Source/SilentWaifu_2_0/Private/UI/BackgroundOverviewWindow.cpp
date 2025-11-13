
#include "UI/BackgroundOverviewWindow.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "GameMode/Helpers/BackgroundManager.h"


void UBackgroundOverviewWindow::Init(UTexture2D* NewImage, int Price, int NewId, const bool IsUnlocked, UBackgroundManager* NewBackgroundManager)
{
	if (!NewImage || !NewBackgroundManager) return;
	BackgroundManager = NewBackgroundManager;
	Id = NewId;
	SetImage(NewImage);
	Button_Action->OnClicked.Clear();
	IsUnlocked ?
		(Button_Action->OnClicked.AddDynamic(this, &UBackgroundOverviewWindow::Set),
		SetButtonText("Set"))
	:
		(Button_Action->OnClicked.AddDynamic(this, &UBackgroundOverviewWindow::Unlock),
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


void UBackgroundOverviewWindow::Unlock()
{
	UE_LOG(LogTemp, Warning, TEXT("overview action - Unlock"))
	FSavedBackgroundsData Data;
	Data.Id = Id;
	Data.IsActive = true;
	BackgroundManager->AddUnlockedBackground(Data);
}


void UBackgroundOverviewWindow::Set()
{
	UE_LOG(LogTemp, Warning, TEXT("overview action - Set"))
	BackgroundManager->SetCurrentBackground(Image);
}



