
#include "SaveGame/SilentWaifuSaveGame.h"


void USilentWaifuSaveGame::SetMoney(int const NewMoney)
{
	CurrentMoney = NewMoney;
}


int USilentWaifuSaveGame::GetMoney() const
{
	return CurrentMoney;
}
