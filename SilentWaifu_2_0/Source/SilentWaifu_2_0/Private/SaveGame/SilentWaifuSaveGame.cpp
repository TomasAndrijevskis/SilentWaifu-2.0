
#include "SaveGame/SilentWaifuSaveGame.h"


void USilentWaifuSaveGame::SaveCurrentMoney(const int NewCurrentMoney)
{
	CurrentMoney = NewCurrentMoney;
}


int USilentWaifuSaveGame::GetCurrentMoney() const
{
	return CurrentMoney;
}


void USilentWaifuSaveGame::SaveCharacter(const int Key, const FSavedCharactersData& Data)
{
	SavedCharacters.Add(Key, Data);
}


TMap<int, FSavedCharactersData> USilentWaifuSaveGame::GetCharacters() const
{
	return SavedCharacters;
}


TMap<int, bool> USilentWaifuSaveGame::GetTakenPositions() const
{
	return TakenPositions;
}


void USilentWaifuSaveGame::SaveTakenPositions(const TMap<int, bool>&  Positions)
{
	TakenPositions = Positions;
}


void USilentWaifuSaveGame::SaveShop(const TArray<int>& NewShopCharacters)
{
	ShopCharacters = NewShopCharacters;
}


TArray<int> USilentWaifuSaveGame::GetShop() const
{
	return ShopCharacters;
}


TArray<FSavedBackgroundsData> USilentWaifuSaveGame::GetUnlockedBackgrounds() const
{
	return UnlockedBackgrounds;
}


void USilentWaifuSaveGame::SaveUnlockedBackgrounds(const TArray<FSavedBackgroundsData>& NewUnlockedBackgrounds)
{
	UnlockedBackgrounds = NewUnlockedBackgrounds;
}


void USilentWaifuSaveGame::SaveLimitLevel(const int Level)
{
	MoneyLimitLevel = Level;
}


int USilentWaifuSaveGame::GetLimitLevel() const
{
	return MoneyLimitLevel;
}


FDateTime USilentWaifuSaveGame::GetShutdownTime() const
{
	return ShutdownTime;
}


void USilentWaifuSaveGame::SaveShutdownTime(const FDateTime& NewLastJoinTime)
{
	ShutdownTime = NewLastJoinTime;
}


void USilentWaifuSaveGame::SaveSoundsVolume(const float NewMusicVolume, const float NewSFXVolume)
{
	MusicVolume = NewMusicVolume;
	SFXVolume = NewSFXVolume;
}


float USilentWaifuSaveGame::GetMusicVolume() const
{
	return MusicVolume;
}


float USilentWaifuSaveGame::GetSFXVolume() const
{
	return SFXVolume;
}
