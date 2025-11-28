
#pragma once

#include "CoreMinimal.h"
#include "SavedCharactersData.h"
#include "Engine/GameInstance.h"
#include "SilentWaifuGameInstance.generated.h"


class UBackgroundManager;
class UCharactersManager;
class UMoneyManager;
class ACharacterTemplate;
class USilentWaifuSaveGame;
class ASilentWaifuGameMode;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameModeLoadedSignature);
UCLASS()
class SILENTWAIFU_2_0_API USilentWaifuGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	virtual void Init() override;

	virtual void Shutdown() override;
	
	UFUNCTION()
	void SaveCurrentMoney(int const CurrentMoney);

	void LoadMoney() const;

	void LoadPositions() const;

	void SavePositions();
	
	void SetGameMode(AGameModeBase* NewGameMode);

	UFUNCTION()
	void SaveShop();

	void LoadShop() const;

	void SaveBackgrounds();

	void LoadBackgrounds();

	UFUNCTION()
	void SaveLimitLevel(const int Level);

	void LoadShutdownTime();
	
	FOnGameModeLoadedSignature OnGameModeLoadedDelegate;
	
private:

	void HandleSaveGame();
	
	UFUNCTION()
	void LoadCharacters();
	
	void SaveCharacters();

	void SaveFirstCharacter(int const Key, const FSavedCharactersData& Data) const;

	UFUNCTION()
	void SetManagers();

	void SetDefaultValues();

	UFUNCTION()
	void LoadLimitLevel();

	void SaveShutdownTime();
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ACharacterTemplate> DefaultCharacter;
	
	UPROPERTY()
	FString SlotName = FString("Slot1");
	
	UPROPERTY()
	USilentWaifuSaveGame* SaveGameInstance;
	
	UPROPERTY()
	ASilentWaifuGameMode* GameMode;

	UPROPERTY()
	UMoneyManager* MoneyManager;

	UPROPERTY()
	UCharactersManager* CharactersManager;
	
	UPROPERTY()
	UBackgroundManager* BackgroundManager;
};
