

#include "GameMode/SilentWaifuGameMode.h"


void ASilentWaifuGameMode::BeginPlay()
{
	Super::BeginPlay();
	OnMoneyIncreasedDelegate.AddDynamic(this, &ASilentWaifuGameMode::ShowMoney);
}


void ASilentWaifuGameMode::ShowMoney()
{
	UE_LOG(LogTemp, Warning, TEXT("ShowMoney: %i"), CurrentMoney);
}


void ASilentWaifuGameMode::IncreaseMoney(const int Money)
{
	CurrentMoney += Money;
	OnMoneyIncreasedDelegate.Broadcast();
}
