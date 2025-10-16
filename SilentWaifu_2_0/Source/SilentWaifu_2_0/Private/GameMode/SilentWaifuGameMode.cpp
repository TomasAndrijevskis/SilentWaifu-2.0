
#include "GameMode/SilentWaifuGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGame/SilentWaifuGameInstance.h"


void ASilentWaifuGameMode::BeginPlay()
{
	Super::BeginPlay();
	//UE_LOG(LogTemp, Error, TEXT("GameMode"));
	GameInstance = Cast<USilentWaifuGameInstance>(UGameplayStatics::GetGameInstance(this));
	if (!GameInstance)
	{
		return;
	}
	GameInstance->LoadMoney();
	OnMoneyIncreasedDelegate.AddDynamic(this, &ASilentWaifuGameMode::ShowMoney);
}


void ASilentWaifuGameMode::ShowMoney()
{
	UE_LOG(LogTemp, Warning, TEXT("ShowMoney: %i"), CurrentMoney);
	GameInstance->SaveMoney(CurrentMoney);
}


void ASilentWaifuGameMode::IncreaseMoney(const int Money)
{
	CurrentMoney += Money;
	OnMoneyIncreasedDelegate.Broadcast();
}
