
#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SilentWaifuGameInstance.generated.h"


struct FSavedCharactersData;
class ACharacterTemplate;
class USilentWaifuSaveGame;
class ASilentWaifuGameMode;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameModeAssignedSignature);
UCLASS()
class SILENTWAIFU_2_0_API USilentWaifuGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	virtual void Init() override;
	
	void SaveMoney(int const Money) const;

	void LoadMoney() const;
	
	void SetGameMode(AGameModeBase* NewGameMode);

	FOnGameModeAssignedSignature OnGameModeAssignedDelegate;
	
private:

	void HandleSaveGame();
	
	UFUNCTION()
	void LoadCharacters();

	void SaveCharacter(int const Key, const FSavedCharactersData& Data) const;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ACharacterTemplate> DefaultCharacter;
	
	UPROPERTY()
	FString SlotName = FString("Slot1");
	
	UPROPERTY()
	USilentWaifuSaveGame* SaveGameInstance;
	
	UPROPERTY()
	ASilentWaifuGameMode* GameMode;
};
