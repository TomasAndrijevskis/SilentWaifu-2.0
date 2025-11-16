
#include "UI/BackgroundOverviewWindow.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "GameMode/Helpers/BackgroundManager.h"
#include "UI/ConfirmationWindow.h"
#include "UI/WidgetReferenceDataAsset.h"
#include "UI/Screens/MainScreen.h"


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
		Button_Action->OnClicked.AddDynamic(this, &UBackgroundOverviewWindow::SetBackground)
	:
		(Button_Action->OnClicked.AddDynamic(this, &UBackgroundOverviewWindow::CreateConfirmationWindow),
		SetButtonText(FString::FromInt(Price)));
}


void UBackgroundOverviewWindow::CreateConfirmationWindow()
{
	if (!WidgetReferences || !WidgetReferences->MainScreenRef) return;
	WidgetReferences->MainScreenRef->CreateConfirmationWindow();
	if (!WidgetReferences->ConfirmationWindowRef) return;
	WidgetReferences->ConfirmationWindowRef->OnSuccessDelegate.AddDynamic(this, &UBackgroundOverviewWindow::UnlockBackground);
	WidgetReferences->ConfirmationWindowRef->SetPrice(Price);
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
	FSavedBackgroundsData Data;
	Data.Id = Id;
	Data.IsActive = true;
	BackgroundManager->AddUnlockedBackground(Data);
	SetBackground();
}


void UBackgroundOverviewWindow::SetBackground()
{
	BackgroundManager->SetCurrentBackgroundId(Id);
	BackgroundManager->SetCurrentBackgroundImage(Image);
}



