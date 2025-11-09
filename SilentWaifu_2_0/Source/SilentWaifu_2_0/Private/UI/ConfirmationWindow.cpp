
#include "UI/ConfirmationWindow.h"
#include "Components/Button.h"


void UConfirmationWindow::NativeConstruct()
{
	Super::NativeConstruct();
	Button_Confirm->OnClicked.AddDynamic(this, &UConfirmationWindow::UConfirmationWindow::OnConfirmed);
	Button_Cancel->OnClicked.AddDynamic(this, &UConfirmationWindow::OnCanceled);
}


void UConfirmationWindow::OnConfirmed()
{
	UE_LOG(LogTemp, Warning, TEXT("OnConfirmed"));
	OnConfirmedDelegate.Broadcast();
}


void UConfirmationWindow::OnCanceled()
{
	UE_LOG(LogTemp, Warning, TEXT("OnCanceled"));
	OnCanceledDelegate.Broadcast();
}
