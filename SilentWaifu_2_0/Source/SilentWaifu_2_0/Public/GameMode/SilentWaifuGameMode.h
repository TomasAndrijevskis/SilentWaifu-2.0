
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SilentWaifuGameMode.generated.h"

class UMainScreen;
class ACharacterTemplate;
class USilentWaifuGameInstance;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMoneyChangedSignature, const int, Money);

UCLASS()
class SILENTWAIFU_2_0_API ASilentWaifuGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	UFUNCTION()
	void IncreaseMoney(const int Money);

	void DecreaseMoney(const int Money);

	bool HasEnoughMoney(const int Money) const;
	
	UFUNCTION()
	void SpawnCharacters(const TSubclassOf<ACharacterTemplate>& CharacterClass);
	
	FOnMoneyChangedSignature OnMoneyChangedDelegate;

protected:

	virtual void BeginPlay() override;
	
private:

	void CreateMainScreenWidget();
	
	UPROPERTY()
	USilentWaifuGameInstance* GameInstance;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UMainScreen> MainScreenWidgetClass;

	UPROPERTY()
	UMainScreen* MainScreenWidgetRef;
	
	UPROPERTY()
	int CurrentMoney = 0;
};
