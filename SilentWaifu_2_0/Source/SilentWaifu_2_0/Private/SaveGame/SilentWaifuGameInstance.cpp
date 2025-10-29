
#include "SaveGame/SilentWaifuGameInstance.h"
#include "Character/CharacterTemplate.h"
#include "GameMode/SilentWaifuGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGame/SilentWaifuSaveGame.h"


void USilentWaifuGameInstance::Init()
{
	Super::Init();
	HandleSaveGame();
	OnGameModeLoadedDelegate.AddDynamic(this, &USilentWaifuGameInstance::LoadCharacters);
}

void USilentWaifuGameInstance::Shutdown()
{
	SavePositions();
	SaveCharacters();
	Super::Shutdown();
}


void USilentWaifuGameInstance::HandleSaveGame()
{
	SaveGameInstance = Cast<USilentWaifuSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));
	if (!SaveGameInstance)
	{
		SaveGameInstance = Cast<USilentWaifuSaveGame>(UGameplayStatics::CreateSaveGameObject(USilentWaifuSaveGame::StaticClass()));
		FSavedCharactersData Data;
		Data.CharacterClass = DefaultCharacter;
		Data.bIsOnScreen = false;
		Data.CharacterId = 1;
		SaveFirstCharacter(1, Data);
		SaveMaxMoney(100);
		UE_LOG(LogTemp, Warning, TEXT("First character saved"));
	}
}


bool USilentWaifuGameInstance::IsCharacterUnlocked(const TSubclassOf<ACharacterTemplate>& Character) const
{
	for (auto const c : GameMode->GetAvailableCharacters())
	{
		if (c.Value.CharacterClass == Character)
		{
			UE_LOG(LogTemp, Warning, TEXT("Character unlocked"));
			return true;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Character locked"));
	return false;
}


void USilentWaifuGameInstance::LoadCharacters()
{
	if (!GameMode) return;
	for (auto const Character : SaveGameInstance->GetCharacters())
	{
		GameMode->OnCharacterAddedDelegate.Broadcast(Character.Key, Character.Value);
	}
	GameMode->OnCharactersLoadedDelegate.Broadcast();
}


void USilentWaifuGameInstance::SaveFirstCharacter(int const Key, const FSavedCharactersData& Data) const
{
	SaveGameInstance->SaveCharacter(Key, Data);
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SlotName, 0);
}


void USilentWaifuGameInstance::SaveCharacters()
{
	for (auto Character : GameMode->GetAvailableCharacters())
	{
		UE_LOG(LogTemp, Warning, TEXT("Character saved: %i"), Character.Key);
		SaveGameInstance->SaveCharacter(Character.Key, Character.Value);
	}
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SlotName, 0);
}


void USilentWaifuGameInstance::SetGameMode(AGameModeBase* NewGameMode)
{
	GameMode = static_cast<ASilentWaifuGameMode*>(NewGameMode);
	OnGameModeLoadedDelegate.Broadcast();
}


void USilentWaifuGameInstance::SaveCurrentMoney(int const CurrentMoney)
{
	SaveGameInstance->SaveCurrentMoney(CurrentMoney);
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SlotName, 0);
}


void USilentWaifuGameInstance::SaveMaxMoney(int const MaxMoney)
{
	SaveGameInstance->SaveMaxMoney(MaxMoney);
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SlotName, 0);
}


void USilentWaifuGameInstance::LoadMoney() const
{
	if (!GameMode) return;
	GameMode->SetMaxMoney(SaveGameInstance->GetMaxMoney());
	GameMode->IncreaseMoney(SaveGameInstance->GetCurrentMoney());
}


void USilentWaifuGameInstance::LoadPositions() const
{
	if (!GameMode) return;
	for (auto const Position : SaveGameInstance->GetTakenPositions())
	{
		GameMode->AddTakenPosition(Position.Key, Position.Value);
	}
}


void USilentWaifuGameInstance::SavePositions()
{
	/*for (auto const Position : GameMode->GetTakenPositions())
	{
		UE_LOG(LogTemp, Warning, TEXT("Save Position:%i, value: %i"), Position.Key, Position.Value);
		//SaveGameInstance->SaveTakenPositions(Position.Key, Position.Value);
	}*/
	SaveGameInstance->SaveTakenPositions(GameMode->GetTakenPositions());
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SlotName, 0);
}

