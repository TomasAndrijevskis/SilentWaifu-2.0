
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ConfirmationWindow.generated.h"


class UButton;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnConfirmedSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCanceledSignature);
UCLASS()
class SILENTWAIFU_2_0_API UConfirmationWindow : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;
	
	FOnConfirmedSignature OnConfirmedDelegate;

	FOnCanceledSignature OnCanceledDelegate;
	
private:

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Confirm;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Cancel;

	UFUNCTION()
	void OnConfirmed();

	UFUNCTION()
	void OnCanceled();
};
