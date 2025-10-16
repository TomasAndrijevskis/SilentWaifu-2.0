
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SilentWaifuSaveGame.generated.h"


UCLASS()
class SILENTWAIFU_2_0_API USilentWaifuSaveGame : public USaveGame
{
	GENERATED_BODY()

public:

	UFUNCTION()
	void SetMoney(int const NewMoney);

	UFUNCTION()
	int GetMoney() const;
	
private:
	UPROPERTY()
	int CurrentMoney;
};
