
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
	void SetMoney(int const NewMoney);

	UFUNCTION()
	int GetMoney() const;

	UFUNCTION()
	void SaveCharacter(const int Key, const FSavedCharactersData& Data);
	
	UFUNCTION()
	TMap<int, FSavedCharactersData> GetCharacters() const;

	UFUNCTION()
	TMap<int, bool> GetTakenPositions() const;

	UFUNCTION()
	void SaveTakenPositions(const int Key, const bool Value);
	
private:
	
	UPROPERTY()
	int CurrentMoney;

	UPROPERTY()
	TMap<int, FSavedCharactersData> SavedCharacters;

	UPROPERTY()
	TMap<int, bool>  TakenPositions;
};
