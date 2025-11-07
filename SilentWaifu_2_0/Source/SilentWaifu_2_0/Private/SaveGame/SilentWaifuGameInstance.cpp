
#include "SaveGame/SilentWaifuGameInstance.h"
#include "GameMode/SilentWaifuGameMode.h"
#include "GameMode/Helpers/CharactersManager.h"
#include "GameMode/Helpers/MoneyManager.h"
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
	SaveShop();
	Super::Shutdown();
}


void USilentWaifuGameInstance::HandleSaveGame()
{
	SaveGameInstance = Cast<USilentWaifuSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));
	if (!SaveGameInstance) return;
	SaveGameInstance = Cast<USilentWaifuSaveGame>(UGameplayStatics::CreateSaveGameObject(USilentWaifuSaveGame::StaticClass()));
	FSavedCharactersData Data;
	Data.CharacterClass = DefaultCharacter;
	Data.bIsOnScreen = false;
	Data.CharacterId = 1;
	Data.Level = 1;
	SaveFirstCharacter(1, Data);
	SaveMaxMoney(100);
}


void USilentWaifuGameInstance::LoadCharacters()
{
	if (!GameMode) return;
	for (const auto& Character : SaveGameInstance->GetCharacters())
	{
		GameMode->CharactersManager->OnCharacterAddedDelegate.Broadcast(Character.Key, Character.Value);
	}
	GameMode->OnCharactersLoadedDelegate.Broadcast();
}


void USilentWaifuGameInstance::SaveFirstCharacter(int const Key, const FSavedCharactersData& Data) const
{
	if (!SaveGameInstance) return;
	SaveGameInstance->SaveCharacter(Key, Data);
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SlotName, 0);
}


void USilentWaifuGameInstance::SaveCharacters()
{
	if (!SaveGameInstance) return;
	for (const auto& Character : GameMode->CharactersManager->GetAvailableCharacters())
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


void USilentWaifuGameInstance::SaveCurrentMoney(int const CurrentMoney)
{
	if (!SaveGameInstance) return;
	SaveGameInstance->SaveCurrentMoney(CurrentMoney);
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SlotName, 0);
}


void USilentWaifuGameInstance::SaveMaxMoney(int const MaxMoney)
{
	if (!SaveGameInstance) return;
	SaveGameInstance->SaveMaxMoney(MaxMoney);
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SlotName, 0);
}


void USilentWaifuGameInstance::LoadMoney() const
{
	if (!GameMode || !SaveGameInstance) return;
	GameMode->MoneyManager->SetMaxMoney(SaveGameInstance->GetMaxMoney());
	GameMode->MoneyManager->IncreaseMoney(SaveGameInstance->GetCurrentMoney());
}


void USilentWaifuGameInstance::LoadPositions() const
{
	if (!GameMode || !SaveGameInstance) return;
	for (const auto& Position : SaveGameInstance->GetTakenPositions())
	{
		GameMode->CharactersManager->AddTakenPosition(Position.Key, Position.Value);
	}
}


void USilentWaifuGameInstance::SavePositions()
{
	if (!SaveGameInstance) return;
	SaveGameInstance->SaveTakenPositions(GameMode->CharactersManager->GetTakenPositions());
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SlotName, 0);
}


void USilentWaifuGameInstance::SaveShop()
{
	if (!SaveGameInstance) return;
	SaveGameInstance->SaveShop(GameMode->CharactersManager->GetShopCharacters());
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SlotName, 0);
}


void USilentWaifuGameInstance::LoadShop() const
{
	if (!GameMode || !SaveGameInstance) return;
	GameMode->CharactersManager->SetShopCharacters(SaveGameInstance->GetShop());
}