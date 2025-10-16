
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SilentWaifuGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMoneyIncreasedSignature);
UCLASS()
class SILENTWAIFU_2_0_API ASilentWaifuGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	UFUNCTION()
	void ShowMoney();

	UFUNCTION()
	void IncreaseMoney(const int Money);

	FOnMoneyIncreasedSignature OnMoneyIncreasedDelegate;

protected:

	virtual void BeginPlay() override;
	
private:

	UPROPERTY()
	int CurrentMoney;
};
