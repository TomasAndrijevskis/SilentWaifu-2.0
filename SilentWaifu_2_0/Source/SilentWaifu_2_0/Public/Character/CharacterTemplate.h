
#pragma once

#include "CoreMinimal.h"
#include "DataTables/CharacterData.h"
#include "GameFramework/Actor.h"
#include "CharacterTemplate.generated.h"

class UMoneyManager;
class ASilentWaifuGameMode;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCharacterLoadedSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnValuesUpdatedSignature);
UCLASS()
class SILENTWAIFU_2_0_API ACharacterTemplate : public AActor
{
	GENERATED_BODY()
	
public:

	void SetValues(const int NewLevel, const int NewId);

	void UpdateLevel(const int NewLevel);
	
	FOnCharacterLoadedSignature OnCharacterLoadedDelegate;

	FOnValuesUpdatedSignature OnValuesUpdatedDelegate;
	
protected:

	virtual void BeginPlay() override;

private:

	UFUNCTION()
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

	UPROPERTY()
	UMoneyManager* MoneyManager;
	
	FCharacterData* CharacterRow;
	
	FTimerHandle TimerHandle;
};
