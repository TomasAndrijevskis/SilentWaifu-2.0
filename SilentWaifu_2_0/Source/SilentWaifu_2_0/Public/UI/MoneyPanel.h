
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MoneyPanel.generated.h"


class UHorizontalBox;
class UWidgetReferenceDataAsset;
class UButton;
class UMoneyManager;
class ASilentWaifuGameMode;
class UTextBlock;

UCLASS()
class SILENTWAIFU_2_0_API UMoneyPanel : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;
	
private:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_CurrentMoney;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_MaxMoney;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Action;

	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* HorizontalBox_AdditionalInfo;
	
	void BindDelegates();

	UFUNCTION()
	void UpdateCurrentMoney(int const Money);

	UFUNCTION()
	void UpdateMaxMoney(int const Money);

	UFUNCTION()
	void CreateAdditionPanel();

	UFUNCTION()
	void RemoveAdditionalPanel();

	void RebindButtonAction(const bool DoesPanelExists);
	
	UPROPERTY()
	ASilentWaifuGameMode* GameMode;
	
	UPROPERTY()
	UMoneyManager* MoneyManager;

	UPROPERTY(EditAnywhere)
	UWidgetReferenceDataAsset* WidgetReferences;
};
