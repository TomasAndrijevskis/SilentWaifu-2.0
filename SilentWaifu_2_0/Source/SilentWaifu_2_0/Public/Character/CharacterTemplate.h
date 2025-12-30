
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
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWasPreviouslyOnScreenSignature, bool, WasOnScreen);
UCLASS()
class SILENTWAIFU_2_0_API ACharacterTemplate : public AActor
{
	GENERATED_BODY()
	
public:

	void SetValues(const int NewId, const int NewLevel, const int NewTimeLeft);

	void UpdateLevel(const int NewLevel);

	int GetMoneyPerMinute() const;

	virtual int GetMoneyPerHour() const;
	
	int GetId() const;

	float GetLeftTime() const;

	void ActivateAbility();
	
	FOnCharacterLoadedSignature OnCharacterLoadedDelegate;

	FOnValuesUpdatedSignature OnValuesUpdatedDelegate;

	FWasPreviouslyOnScreenSignature WasPreviouslyOnScreenDelegate;
	
protected:

	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void SetMoney();

	void SetCharacterRow();

	void IncreaseMoney() const;

	void IncreaseMoneyAtTime(const FDateTime& Time) const;
	
	virtual int GetMoneyMultiplier(const FDateTime& Time) const;
	
	FCharacterData* GetCharacterRow() const;
	
	UPROPERTY(EditAnywhere)
	UAbilityComponent_Base* AbilityComponent;

	UPROPERTY()
	UCharactersManager* CharactersManager;

	UPROPERTY()
	ASilentWaifuGameMode* GameMode;

	UPROPERTY(VisibleAnywhere)
	int MoneyPerMinute;
	
	UPROPERTY(VisibleAnywhere)
	int Level;
	
	int TimeLeft;

	int IncomeInterval = 60;
	
private:

	UFUNCTION()
	void EnableIncomeTimer();

	UFUNCTION()
	void CheckTime();

	UFUNCTION()
	void HandleOfflineIncome(const bool WasOnScreen);
	
	UPROPERTY(EditAnywhere)
	UDataTable* CharacterDataTable;

	UPROPERTY(VisibleAnywhere)
	int Id;

	UPROPERTY()
	UMoneyManager* MoneyManager;
	
	FTimerHandle TimerHandle;

	FCharacterData* CharacterRow;
};
