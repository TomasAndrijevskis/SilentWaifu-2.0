
#include "SaveGame/SilentWaifuSaveGame.h"


void USilentWaifuSaveGame::SetMoney(int const NewMoney)
{
	CurrentMoney = NewMoney;
}


int USilentWaifuSaveGame::GetMoney() const
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


void USilentWaifuSaveGame::SaveTakenPositions(const int Key, const bool Value)
{
	TakenPositions.Add(Key, Value);
}
