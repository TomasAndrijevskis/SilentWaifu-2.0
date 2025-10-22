
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SaveGame/SavedCharactersData.h"
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

	UFUNCTION()
	void SetAvailableCharacters(int const Key, const FSavedCharactersData& Data);

	TMap<int, FSavedCharactersData> GetAvailableCharacters() const;
	
	FOnMoneyChangedSignature OnMoneyChangedDelegate;
	
protected:

	virtual void BeginPlay() override;
	
private:

	void CreateMainScreenWidget();

	void SetInputSettings() const;
	
	UPROPERTY()
	USilentWaifuGameInstance* GameInstance;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UMainScreen> MainScreenWidgetClass;

	UPROPERTY()
	UMainScreen* MainScreenWidgetRef;

	UPROPERTY()
	TMap<int, FSavedCharactersData> AvailableCharacters;
	
	UPROPERTY()
	int CurrentMoney = 0;
};
