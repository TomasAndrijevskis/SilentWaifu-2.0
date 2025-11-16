
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ConfirmationWindow.generated.h"


class UWidgetReferenceDataAsset;
class UMoneyManager;
class ASilentWaifuGameMode;
class UButton;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnConfirmedSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCanceledSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSuccessSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFailSignature);
UCLASS()
class SILENTWAIFU_2_0_API UConfirmationWindow : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	void SetPrice(int NewPrice);
	
	FOnConfirmedSignature OnConfirmedDelegate;

	FOnCanceledSignature OnCanceledDelegate;

	FOnSuccessSignature OnSuccessDelegate;

	FOnFailSignature OnFailDelegate;
	
private:

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Confirm;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Cancel;

	UFUNCTION()
	void OnConfirmed();

	UFUNCTION()
	void OnCanceled();

	UFUNCTION()
	void OnFail();

	UFUNCTION()
	void OnSuccess();
	
	UFUNCTION()
	void CheckMoney();

	void CreateNotification(const FText& Message);

	UFUNCTION()
	void RemoveNotificationReference();
	
	UPROPERTY()
	ASilentWaifuGameMode* GameMode;

	UPROPERTY()
	UMoneyManager* MoneyManager;

	UPROPERTY(EditAnywhere)
	UWidgetReferenceDataAsset* WidgetReferences;
	
	int Price;
};
