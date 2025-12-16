
#include "UI/ConfirmationWindow.h"
#include "Components/Button.h"
#include "GameMode/SilentWaifuGameMode.h"
#include "GameMode/Helpers/MoneyManager.h"
#include "Kismet/GameplayStatics.h"
#include "UI/NotificationWindow.h"
#include "UI/WidgetReferenceDataAsset.h"


void UConfirmationWindow::NativeConstruct()
{
	Super::NativeConstruct();
	UE_LOG(LogTemp, Warning, TEXT("NativeConstruct"));
	GameMode = Cast<ASilentWaifuGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!GameMode) return;
	MoneyManager = GameMode->MoneyManager;
	BindActions();
	BindDelegates();
}


void UConfirmationWindow::BindDelegates()
{
	IsEvent ?
		OnConfirmedDelegate.AddUniqueDynamic(this, &UConfirmationWindow::CheckEventMoney) :
		OnConfirmedDelegate.AddUniqueDynamic(this, &UConfirmationWindow::CheckMoney);
}

void UConfirmationWindow::BindActions()
{
	Button_Confirm->OnClicked.AddDynamic(this, &UConfirmationWindow::OnConfirmed);
	Button_Cancel->OnClicked.AddDynamic(this, &UConfirmationWindow::OnCanceled);
}


void UConfirmationWindow::SetPrice(const int NewPrice)
{
	UE_LOG(LogTemp, Warning, TEXT("SetPrice"));
	Price = NewPrice;
}


void UConfirmationWindow::CheckMoney()
{
	if (!MoneyManager || !MoneyManager->HasEnoughMoney(Price))
	{
		OnFail();
		return;
	}
	OnSuccess();
}


void UConfirmationWindow::CheckEventMoney()
{
	if (!MoneyManager || !MoneyManager->HasEnoughEventMoney(Price))
	{
		OnFail();
		return;
	}
	OnSuccess();
}


void UConfirmationWindow::OnConfirmed()
{
	OnConfirmedDelegate.Broadcast();
}


void UConfirmationWindow::OnCanceled()
{
	OnCanceledDelegate.Broadcast();
}


void UConfirmationWindow::OnFail()
{
	CreateNotification(FText::FromString(TEXT("Fail")));
}


void UConfirmationWindow::OnSuccess()
{
	IsEvent ?
		MoneyManager->DecreaseEventMoney(Price) :
		MoneyManager->DecreaseMoney(Price);
	CreateNotification(FText::FromString(TEXT("Success")));
	OnSuccessDelegate.Broadcast();
}


void UConfirmationWindow::CreateNotification(const FText& Message)
{
	if (!WidgetReferences || !WidgetReferences->NotificationWindowClass) return;
	WidgetReferences->NotificationWindowRef = Cast<UNotificationWindow>(CreateWidget(GetWorld(), WidgetReferences->NotificationWindowClass));
	if (!WidgetReferences->NotificationWindowRef) return;
	WidgetReferences->NotificationWindowRef->AddToViewport(5);
	WidgetReferences->NotificationWindowRef->SetText(Message);
	WidgetReferences->NotificationWindowRef->OnAnimFinishedDelegate.AddDynamic(this, &UConfirmationWindow::RemoveNotificationReference);
}


void UConfirmationWindow::RemoveNotificationReference()
{
	if (!WidgetReferences || !WidgetReferences->NotificationWindowRef) return;
	WidgetReferences->NotificationWindowRef->RemoveFromParent();
	WidgetReferences->NotificationWindowRef = nullptr;
}


void UConfirmationWindow::SetIsEvent(const bool bIsEvent)
{
	IsEvent = bIsEvent;
}
