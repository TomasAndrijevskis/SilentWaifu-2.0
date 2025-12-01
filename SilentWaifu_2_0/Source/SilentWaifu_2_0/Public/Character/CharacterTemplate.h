
#pragma once

#include "CoreMinimal.h"
#include "DataTables/CharacterData.h"
#include "GameFramework/Actor.h"
#include "CharacterTemplate.generated.h"

class UCharactersManager;
class UMoneyManager;
class ASilentWaifuGameMode;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCharacterLoadedSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnValuesUpdatedSignature);
UCLASS()
class SILENTWAIFU_2_0_API ACharacterTemplate : public AActor
{
	GENERATED_BODY()
	
public:

	void SetValues(const int NewId, const int NewLevel, const float TimeLeft);

	void UpdateLevel(const int NewLevel);

	int GetMoneyPerSecond() const;

	int GetId() const;

	float GetLeftTime() const;
	
	FOnCharacterLoadedSignature OnCharacterLoadedDelegate;

	FOnValuesUpdatedSignature OnValuesUpdatedDelegate;
	
protected:

	virtual void BeginPlay() override;

private:

	UFUNCTION()
	void SetMoney();
	
	void IncreaseMoney();

	UFUNCTION()
	void EnableTimer();

	UFUNCTION()
	void CheckTime();
	
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

	UPROPERTY()
	UMoneyManager* MoneyManager;

	UPROPERTY()
	UCharactersManager* CharactersManager;
	
	FCharacterData* CharacterRow;
	
	FTimerHandle TimerHandle;

	float IncomeInterval = 10;

	float TempTime;
};
