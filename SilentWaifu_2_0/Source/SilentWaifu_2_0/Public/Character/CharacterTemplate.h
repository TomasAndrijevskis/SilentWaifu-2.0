
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CharacterTemplate.generated.h"

class ASilentWaifuGameMode;
UCLASS()
class SILENTWAIFU_2_0_API ACharacterTemplate : public AActor
{
	GENERATED_BODY()
	
public:	


protected:

	virtual void BeginPlay() override;

private:

	UFUNCTION()
	void IncreaseMoney() const;
	
	UPROPERTY(EditAnywhere)
	int MoneyPerSecond = 5;

	UPROPERTY()
	ASilentWaifuGameMode* GameMode;
};
