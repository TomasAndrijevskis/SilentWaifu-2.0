
#include "UI/NotificationWindow.h"
#include "Components/TextBlock.h"


void UNotificationWindow::NativeConstruct()
{
	Super::NativeConstruct();
	PlayAnimation(FadeIn, 0.f, 1, EUMGSequencePlayMode::Forward, 1.0f, false);
}


void UNotificationWindow::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
	Super::OnAnimationFinished_Implementation(Animation);
}



void UNotificationWindow::SetText(const FText& MessageText)
{
	Text_Message->SetText(MessageText);
}

