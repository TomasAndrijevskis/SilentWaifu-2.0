
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

	int GetMoneyPerHour() const;
	
	int GetId() const;

	float GetLeftTime() const;

	void ActivateAbility();
	
	FOnCharacterLoadedSignature OnCharacterLoadedDelegate;

	FOnValuesUpdatedSignature OnValuesUpdatedDelegate;

	FWasPreviouslyOnScreenSignature WasPreviouslyOnScreenDelegate;
	
protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UAbilityComponent_Base* AbilityComponent;
	
private:

	UFUNCTION()
	void SetMoney();
	
	void IncreaseMoney() const;

	UFUNCTION()
	void EnableTimer();

	UFUNCTION()
	void CheckTime();
	
	void GetCharacterRow();

	UFUNCTION()
	void HandleOfflineIncome(const bool WasOnScreen);
	
	UPROPERTY()
	ASilentWaifuGameMode* GameMode;

	UPROPERTY(EditAnywhere)
	UDataTable* CharacterDataTable;
	
	UPROPERTY(VisibleAnywhere)
	int MoneyPerMinute;

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

	int IncomeInterval = 60;

	int TimeLeft;
};
