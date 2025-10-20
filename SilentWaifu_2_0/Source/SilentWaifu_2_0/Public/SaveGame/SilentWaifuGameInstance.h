
#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SilentWaifuGameInstance.generated.h"


struct FSavedCharactersData;
class ACharacterTemplate;
class USilentWaifuSaveGame;
class ASilentWaifuGameMode;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameModeLoadedSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCharacterAddedSignature, int const, CharacterId, const FSavedCharactersData&, CharacterData);
UCLASS()
class SILENTWAIFU_2_0_API USilentWaifuGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	virtual void Init() override;
	
	void SaveMoney(int const Money) const;

	void LoadMoney() const;
	
	void SetGameMode(AGameModeBase* NewGameMode);

	FOnGameModeLoadedSignature OnGameModeLoadedDelegate;
	
	FOnCharacterAddedSignature OnCharacterAddedDelegate;
	
private:

	void HandleSaveGame();
	
	UFUNCTION()
	void LoadCharacters();

	UFUNCTION()
	void SaveCharacter(int const Key, const FSavedCharactersData& Data);

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ACharacterTemplate> DefaultCharacter;
	
	UPROPERTY()
	FString SlotName = FString("Slot1");
	
	UPROPERTY()
	USilentWaifuSaveGame* SaveGameInstance;
	
	UPROPERTY()
	ASilentWaifuGameMode* GameMode;
};
