
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterAbilityCooldownPanel.generated.h"


class UTextBlock;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCooldownEndedSignature);
UCLASS()
class SILENTWAIFU_2_0_API UCharacterAbilityCooldownPanel : public UUserWidget
{
	GENERATED_BODY()

public:

	void Init(const FDateTime NewCooldownEndTime);

	virtual void NativeConstruct() override;

	FOnCooldownEndedSignature OnCooldownEndedDelegate;
	
private:
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_AbilityCooldownValue;
	
	void EnableAbilityCooldownTimer();

	void EnableAliveTimer();
	
	UFUNCTION()
	void CreateAbilityCooldown();

	void SetCooldownText(const FString& Text);

	void OnAliveTimerEnded();
	
	FDateTime CooldownEndTime;

	float AliveTime = 4;
	
	FTimerHandle AbilityCooldownTimerHandle;

	FTimerHandle AliveTimerHandle;
};

