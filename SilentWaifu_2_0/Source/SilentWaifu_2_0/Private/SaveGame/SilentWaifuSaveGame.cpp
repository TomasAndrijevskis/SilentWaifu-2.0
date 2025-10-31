
#include "SaveGame/SilentWaifuSaveGame.h"


void USilentWaifuSaveGame::SaveCurrentMoney(int const NewCurrentMoney)
{
	CurrentMoney = NewCurrentMoney;
}


void USilentWaifuSaveGame::SaveMaxMoney(int const NewMaxMoney)
{
	MaxMoney = NewMaxMoney;
}


int USilentWaifuSaveGame::GetCurrentMoney() const
{
	return CurrentMoney;
}


int USilentWaifuSaveGame::GetMaxMoney() const
{
	return MaxMoney;
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
	//TakenPositions.Add(Key, Value);
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
