
#include "SaveGame/SilentWaifuSaveGame.h"


void USilentWaifuSaveGame::SetMoney(int const NewMoney)
{
	CurrentMoney = NewMoney;
}


int USilentWaifuSaveGame::GetMoney() const
{
	return CurrentMoney;
}


void USilentWaifuSaveGame::SaveCharacter(int const Key, const FSavedCharactersData& Data)
{
	SavedCharacters.Add(Key, Data);
}


TMap<int, FSavedCharactersData> USilentWaifuSaveGame::GetCharactersData() const
{
	return SavedCharacters;
}
