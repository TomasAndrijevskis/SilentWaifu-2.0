
#pragma once

#include "CoreMinimal.h"
#include "SavedCharactersData.h"
#include "GameFramework/SaveGame.h"
#include "SilentWaifuSaveGame.generated.h"


UCLASS()
class SILENTWAIFU_2_0_API USilentWaifuSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	
	UFUNCTION()
	void SaveCurrentMoney(int const NewCurrentMoney);

	UFUNCTION()
	void SaveMaxMoney(int const NewMaxMoney);

	UFUNCTION()
	int GetCurrentMoney() const;

	UFUNCTION()
	int GetMaxMoney() const;

	UFUNCTION()
	void SaveCharacter(const int Key, const FSavedCharactersData& Data);
	
	UFUNCTION()
	TMap<int, FSavedCharactersData> GetCharacters() const;

	UFUNCTION()
	TMap<int, bool> GetTakenPositions() const;

	UFUNCTION()
	void SaveTakenPositions(const TMap<int, bool>&  Positions);

	UFUNCTION()
	void SaveShop(const TArray<int>& NewShopCharacters);

	UFUNCTION()
	TArray<int> GetShop() const;
	
private:
	
	UPROPERTY()
	int CurrentMoney;

	UPROPERTY()
	int MaxMoney;

	UPROPERTY()
	TMap<int, FSavedCharactersData> SavedCharacters;

	UPROPERTY()
	TMap<int, bool> TakenPositions;

	UPROPERTY()
	TArray<int> ShopCharacters;
};
