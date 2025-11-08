
#pragma once

#include "CoreMinimal.h"
#include "SaveGame/SavedCharactersData.h"
#include "CharactersManager.generated.h"

class ASilentWaifuGameMode;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCharacterAddedSignature, int const, CharacterId, const FSavedCharactersData&, CharacterData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterUpgradeSignature, const int, CharacterId);
UCLASS()
class SILENTWAIFU_2_0_API UCharactersManager : public UObject
{
	GENERATED_BODY()

public:

	//virtual void BeginPlay() override;
	void Init();
	
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
	TArray<int>& GetShopCharacters();

	bool IsCharacterUnlocked(const int CharacterId) const;

	FOnCharacterAddedSignature OnCharacterAddedDelegate;

	FOnCharacterUpgradeSignature OnCharacterUpgradeDelegate;
	
private:

	UFUNCTION()
	void UpdateCharacterLevel(const int CharacterId);

	UPROPERTY()
	ASilentWaifuGameMode* GameMode;
	
	UPROPERTY()
	TMap<int, FSavedCharactersData> AvailableCharacters;

	UPROPERTY()
	TMap<int, bool> TakenPositions;

	UPROPERTY()
	TArray<int> ShopCharacters;
	
	int CurrentSpawnPosition = -1;
	
};
