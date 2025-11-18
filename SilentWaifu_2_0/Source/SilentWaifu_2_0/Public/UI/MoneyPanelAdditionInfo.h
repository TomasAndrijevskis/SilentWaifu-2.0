
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MoneyPanelAdditionInfo.generated.h"


class ASilentWaifuGameMode;
class UTextBlock;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTimerFinishedSignature);
UCLASS()
class SILENTWAIFU_2_0_API UMoneyPanelAdditionInfo : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	void ClearTimer();
	
	FOnTimerFinishedSignature OnTimerFinishedDelegate;
	
private:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_OverallMoney;
	
	void Countdown();
	
	
	void SetOverallMoney();

	void SetText();

	int OverallMoney;

	float AliveTime = 2;

	FTimerHandle TimerHandle;
};
