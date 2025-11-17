
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MoneyPanel.generated.h"


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

	void BindDelegates();

	UFUNCTION()
	void UpdateCurrentMoney(int const Money);

	UFUNCTION()
	void UpdateMaxMoney(int const Money);
	
	UPROPERTY()
	ASilentWaifuGameMode* GameMode;
	
	UPROPERTY()
	UMoneyManager* MoneyManager;
};
