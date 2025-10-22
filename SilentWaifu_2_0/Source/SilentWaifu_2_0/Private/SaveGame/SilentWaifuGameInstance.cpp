
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
		Data.bIsOnScreen = true;
		Data.CharacterId = 1;
		SaveFirstCharacter(1, Data);
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
		SaveGameInstance->SaveCharacter(Character.Key, Character.Value);
	}
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SlotName, 0);
}


void USilentWaifuGameInstance::SetGameMode(AGameModeBase* NewGameMode)
{
	GameMode = static_cast<ASilentWaifuGameMode*>(NewGameMode);
	OnGameModeLoadedDelegate.Broadcast();
}


void USilentWaifuGameInstance::SaveMoney(int const Money)
{
	SaveGameInstance->SetMoney(Money);
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SlotName, 0);
}


void USilentWaifuGameInstance::LoadMoney() const
{
	if (!GameMode)
	{
		return;
	}
	GameMode->IncreaseMoney(SaveGameInstance->GetMoney());
}

