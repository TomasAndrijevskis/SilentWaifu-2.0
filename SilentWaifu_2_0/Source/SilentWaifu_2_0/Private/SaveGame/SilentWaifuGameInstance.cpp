
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
	OnCharacterAddedDelegate.AddDynamic(this, &USilentWaifuGameInstance::SaveCharacter);
}


void USilentWaifuGameInstance::HandleSaveGame()
{
	SaveGameInstance = Cast<USilentWaifuSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));
	if (!SaveGameInstance)
	{
		SaveGameInstance = Cast<USilentWaifuSaveGame>(UGameplayStatics::CreateSaveGameObject(USilentWaifuSaveGame::StaticClass()));
		FSavedCharactersData Data;
		Data.CharacterClass = DefaultCharacter;
		SaveCharacter(1, Data);
	}
}


bool USilentWaifuGameInstance::IsCharacterUnlocked(const TSubclassOf<ACharacterTemplate>& Character) const
{
	for (auto const c : SaveGameInstance->GetCharacters())
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
		GameMode->SpawnCharacters(Character.Value.CharacterClass);
		UE_LOG(LogTemp, Warning, TEXT("Loading character %d"), Character.Key);
	}
}


void USilentWaifuGameInstance::SaveCharacter(int const Key, const FSavedCharactersData& Data)
{
	SaveGameInstance->SaveCharacter(Key, Data);
	UE_LOG(LogTemp, Warning, TEXT("Saving character"));
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SlotName, 0);
}


void USilentWaifuGameInstance::SetGameMode(AGameModeBase* NewGameMode)
{
	GameMode = static_cast<ASilentWaifuGameMode*>(NewGameMode);
	OnGameModeLoadedDelegate.Broadcast();
}


void USilentWaifuGameInstance::SaveMoney(int const Money) const
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

