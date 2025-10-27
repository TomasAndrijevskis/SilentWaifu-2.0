
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SaveGame/SavedCharactersData.h"
#include "SilentWaifuGameMode.generated.h"


class UWidgetReferenceDataAsset;
class UMainScreen;
class ACharacterTemplate;
class USilentWaifuGameInstance;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMoneyChangedSignature, const int, Money);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCharactersLoadedSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCharacterAddedSignature, int const, CharacterId, const FSavedCharactersData&, CharacterData);
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
	void SpawnCharacters();

	UFUNCTION()
	void SpawnCharacter(const int CharacterId);
	
	void RemoveCharacter(const int CharacterId);
	
	UFUNCTION()
	void AddAvailableCharacter(const int Key, const FSavedCharactersData& Data);

	UFUNCTION()
	void SortCharactersById();

	void SetCurrentSpawnPosition(const int NewSpawnPosition);
	
	void AddTakenPosition(const int Key, const bool Value);
	
	TMap<int, FSavedCharactersData> GetAvailableCharacters() const;

	TMap<int, bool>& GetTakenPositions();
	
	FOnMoneyChangedSignature OnMoneyChangedDelegate;

	FOnCharacterAddedSignature OnCharacterAddedDelegate;

	FOnCharactersLoadedSignature OnCharactersLoadedDelegate;
	
protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UWidgetReferenceDataAsset* WidgetReferences;
	
private:

	void HandleGameLoad();
	
	void CreateMainScreenWidget();

	void SetInputSettings() const;
	
	UPROPERTY()
	USilentWaifuGameInstance* GameInstance;

	UPROPERTY()
	TMap<int, FSavedCharactersData> AvailableCharacters;

	UPROPERTY()
	TMap<int, bool> TakenPositions;
	
	UPROPERTY()
	int CurrentMoney = 0;

	int CurrentSpawnPosition = -1;
};
