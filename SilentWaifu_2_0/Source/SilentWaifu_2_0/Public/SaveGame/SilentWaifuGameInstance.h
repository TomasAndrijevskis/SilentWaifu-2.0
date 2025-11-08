
#pragma once

#include "CoreMinimal.h"
#include "SavedCharactersData.h"
#include "Engine/GameInstance.h"
#include "SilentWaifuGameInstance.generated.h"


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

	UFUNCTION()
	void SaveMaxMoney(int const MaxMoney);

	void LoadMoney() const;

	void LoadPositions() const;

	void SavePositions();
	
	void SetGameMode(AGameModeBase* NewGameMode);
	
	void SaveShop();

	void LoadShop() const;
	
	FOnGameModeLoadedSignature OnGameModeLoadedDelegate;
	
private:

	void HandleSaveGame();
	
	UFUNCTION()
	void LoadCharacters();
	
	void SaveCharacters();

	void SaveFirstCharacter(int const Key, const FSavedCharactersData& Data) const;

	UFUNCTION()
	void SetManagers();
	
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
};
