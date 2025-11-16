
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NotificationWindow.generated.h"


class UTextBlock;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAnimFinishedSignature);
UCLASS()
class SILENTWAIFU_2_0_API UNotificationWindow : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;
	
	void SetText(const FText& MessageText);

	virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) override;

	FOnAnimFinishedSignature OnAnimFinishedDelegate;
private:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_Message;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* FadeIn;
};
