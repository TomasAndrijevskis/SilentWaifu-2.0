
#include "SaveGame/SilentWaifuGameInstance.h"
#include "GameMode/SilentWaifuGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGame/SilentWaifuSaveGame.h"


void USilentWaifuGameInstance::Init()
{
	Super::Init();
	//UE_LOG(LogTemp, Error, TEXT("GameInstance"));
	SaveGame = Cast<USilentWaifuSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));
	if (!SaveGame)
	{
		SaveGame = Cast<USilentWaifuSaveGame>(UGameplayStatics::CreateSaveGameObject(USilentWaifuSaveGame::StaticClass()));
	}
	
}

void USilentWaifuGameInstance::SaveMoney(int const Money) const
{
	SaveGame->SetMoney(Money);
	UE_LOG(LogTemp, Warning, TEXT("GI|Saving money"));
	UGameplayStatics::SaveGameToSlot(SaveGame, SlotName, 0);
}


void USilentWaifuGameInstance::LoadMoney()
{
	GameMode = Cast<ASilentWaifuGameMode>(UGameplayStatics::GetGameMode(this));
	if (!GameMode)
	{
		return;
	}
	GameMode->IncreaseMoney(SaveGame->GetMoney());
	UE_LOG(LogTemp, Warning, TEXT("GI|Loading money"));
}
