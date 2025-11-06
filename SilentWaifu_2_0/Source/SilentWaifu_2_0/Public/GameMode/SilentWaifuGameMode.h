
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SaveGame/SavedCharactersData.h"
#include "SilentWaifuGameMode.generated.h"


class UMoneyManager;
class UWidgetReferenceDataAsset;
class UMainScreen;
class ACharacterTemplate;
class USilentWaifuGameInstance;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCharactersLoadedSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterUpgradeSignature, const int, CharacterId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCharacterAddedSignature, int const, CharacterId, const FSavedCharactersData&, CharacterData);
UCLASS()
class SILENTWAIFU_2_0_API ASilentWaifuGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION()
	void SpawnCharacters();

	UFUNCTION()
	void SpawnCharacter(const int CharacterId);
	
	void RemoveCharacter(const int CharacterId);
	
	UFUNCTION()
	void AddAvailableCharacter(const int Key, const FSavedCharactersData& Data);
	
	TArray<TPair<int, FSavedCharactersData>> GetSortedCharacters() const;
	
	void SetCurrentSpawnPosition(const int NewSpawnPosition);
	
	void AddTakenPosition(const int Key, const bool Value);
	
	TMap<int, FSavedCharactersData>& GetAvailableCharacters();

	TMap<int, bool>& GetTakenPositions();

	UFUNCTION()
	void SetShopCharacters(const TArray<int>& NewShopCharacters);

	UFUNCTION()
	TArray<int> GetShopCharacters() const;

	bool IsCharacterUnlocked(const int CharacterId) const;

	UPROPERTY()
	UMoneyManager* MoneyManager;
	
	FOnCharacterAddedSignature OnCharacterAddedDelegate;

	FOnCharactersLoadedSignature OnCharactersLoadedDelegate;

	FOnCharacterUpgradeSignature OnCharacterUpgradeDelegate;
	
protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UWidgetReferenceDataAsset* WidgetReferences;
	
private:

	void HandleGameLoad();
	
	void CreateMainScreenWidget();

	void SetInputSettings() const;

	UFUNCTION()
	void UpdateCharacter(const int CharacterId);
	
	UPROPERTY()
	USilentWaifuGameInstance* GameInstance;

	UPROPERTY()
	TMap<int, FSavedCharactersData> AvailableCharacters;

	UPROPERTY()
	TMap<int, bool> TakenPositions;

	UPROPERTY()
	TArray<int> ShopCharacters;
	
	int CurrentSpawnPosition = -1;
};
