
#include "SaveGame/SilentWaifuGameInstance.h"
#include "GameMode/SilentWaifuGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGame/SilentWaifuSaveGame.h"


void USilentWaifuGameInstance::Init()
{
	Super::Init();
	HandleSaveGame();
	OnGameModeAssignedDelegate.AddDynamic(this, &USilentWaifuGameInstance::LoadCharacters);
}


void USilentWaifuGameInstance::HandleSaveGame()
{
	SaveGameInstance = Cast<USilentWaifuSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));
	if (!SaveGameInstance)
	{
		SaveGameInstance = Cast<USilentWaifuSaveGame>(UGameplayStatics::CreateSaveGameObject(USilentWaifuSaveGame::StaticClass()));
		FSavedCharactersData Data;
		Data.CharacterClass = DefaultCharacter;
		SaveCharacter(2, Data);
		SaveCharacter(1, Data);
	}
}


void USilentWaifuGameInstance::LoadCharacters()
{
	for (auto character : SaveGameInstance->GetCharactersData())
	{
		GameMode->SpawnCharacters(character.Value.CharacterClass);
		UE_LOG(LogTemp, Warning, TEXT("Loading character %d"), character.Key);
		//UE_LOG(LogTemp, Warning, TEXT("Loading character %s"), character.Value.CharacterClass->GetName());
	}
}


void USilentWaifuGameInstance::SaveCharacter(int const Key, const FSavedCharactersData& Data) const
{
	SaveGameInstance->SaveCharacter(Key, Data);
}


void USilentWaifuGameInstance::SetGameMode(AGameModeBase* NewGameMode)
{
	GameMode = static_cast<ASilentWaifuGameMode*>(NewGameMode);
	OnGameModeAssignedDelegate.Broadcast();
}


void USilentWaifuGameInstance::SaveMoney(int const Money) const
{
	SaveGameInstance->SetMoney(Money);
	//UE_LOG(LogTemp, Warning, TEXT("GI|Saving money"));
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SlotName, 0);
}


void USilentWaifuGameInstance::LoadMoney() const
{
	if (!GameMode)
	{
		return;
	}
	GameMode->IncreaseMoney(SaveGameInstance->GetMoney());
	UE_LOG(LogTemp, Warning, TEXT("GI|Loading money"));
}
