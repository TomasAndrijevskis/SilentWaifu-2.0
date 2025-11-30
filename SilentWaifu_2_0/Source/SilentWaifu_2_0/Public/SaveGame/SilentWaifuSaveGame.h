
#pragma once

#include "CoreMinimal.h"
#include "SavedBackgroundsData.h"
#include "SavedCharactersData.h"
#include "GameFramework/SaveGame.h"
#include "SilentWaifuSaveGame.generated.h"


UCLASS()
class SILENTWAIFU_2_0_API USilentWaifuSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	
	UFUNCTION()
	void SaveCurrentMoney(const int NewCurrentMoney);
	
	UFUNCTION()
	int GetCurrentMoney() const;

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

	UFUNCTION()
	TArray<FSavedBackgroundsData> GetUnlockedBackgrounds() const;

	UFUNCTION()
	void SaveUnlockedBackgrounds(const TArray<FSavedBackgroundsData>& NewUnlockedBackgrounds);

	void SaveLimitLevel(const int Level);

	int GetLimitLevel() const;

	FDateTime GetShutdownTime() const;

	void SaveShutdownTime(const FDateTime& NewLastJoinTime);

	void SaveSoundsVolume(const float NewMusicVolume, const float NewSFXVolume);

	float GetMusicVolume() const;

	float GetSFXVolume() const;
	
private:
	
	UPROPERTY()
	int CurrentMoney;
	
	UPROPERTY()
	TMap<int, FSavedCharactersData> SavedCharacters;

	UPROPERTY()
	TMap<int, bool> TakenPositions;

	UPROPERTY()
	TArray<int> ShopCharacters;

	UPROPERTY()
	TArray<FSavedBackgroundsData> UnlockedBackgrounds;

	UPROPERTY()
	int MoneyLimitLevel;

	UPROPERTY()
	FDateTime ShutdownTime;

	UPROPERTY()
	float MusicVolume;

	UPROPERTY()
	float SFXVolume;
};
