
#pragma once

#include "CoreMinimal.h"
#include "DataTables/CharacterData.h"
#include "GameFramework/Actor.h"
#include "CharacterTemplate.generated.h"

class ASilentWaifuGameMode;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCharacterLoadedSignature);
UCLASS()
class SILENTWAIFU_2_0_API ACharacterTemplate : public AActor
{
	GENERATED_BODY()
	
public:

	void SetValues(const int NewLevel, const int NewId);

	void UpdateLevel(const int NewLevel);
	
	FOnCharacterLoadedSignature OnCharacterLoadedDelegate;
	
protected:

	virtual void BeginPlay() override;

private:
	
	void SetMoney();
	
	void IncreaseMoney() const;

	UFUNCTION()
	void EnableTimer();

	void GetCharacterRow();
	
	UPROPERTY()
	ASilentWaifuGameMode* GameMode;

	UPROPERTY(EditAnywhere)
	UDataTable* CharacterDataTable;

	UPROPERTY(VisibleAnywhere)
	int MoneyPerSecond;

	UPROPERTY(VisibleAnywhere)
	int Level;

	UPROPERTY(VisibleAnywhere)
	int Id;

	FCharacterData* CharacterRow;
	
	FTimerHandle TimerHandle;
};
