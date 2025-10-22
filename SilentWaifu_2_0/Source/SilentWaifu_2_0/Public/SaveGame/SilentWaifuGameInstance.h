
#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SilentWaifuGameInstance.generated.h"


struct FSavedCharactersData;
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
	void SaveMoney(int const Money);

	void LoadMoney() const;
	
	void SetGameMode(AGameModeBase* NewGameMode);

	bool IsCharacterUnlocked(const TSubclassOf<ACharacterTemplate>& Character) const;
	
	FOnGameModeLoadedSignature OnGameModeLoadedDelegate;
	
private:

	void HandleSaveGame();
	
	UFUNCTION()
	void LoadCharacters();
	
	void SaveCharacters();

	void SaveFirstCharacter(int const Key, const FSavedCharactersData& Data) const;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ACharacterTemplate> DefaultCharacter;
	
	UPROPERTY()
	FString SlotName = FString("Slot1");
	
	UPROPERTY()
	USilentWaifuSaveGame* SaveGameInstance;
	
	UPROPERTY()
	ASilentWaifuGameMode* GameMode;
};
