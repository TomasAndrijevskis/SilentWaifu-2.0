
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
	if (!SaveGameInstance)
	{
		SaveGameInstance = Cast<USilentWaifuSaveGame>(UGameplayStatics::CreateSaveGameObject(USilentWaifuSaveGame::StaticClass()));
		FSavedCharactersData Data;
		Data.CharacterClass = DefaultCharacter;
		Data.bIsOnScreen = false;
		Data.CharacterId = 1;
		Data.Level = 1;
		SaveFirstCharacter(1, Data);
		SaveMaxMoney(100);
	}
}


void USilentWaifuGameInstance::SetGameMode(AGameModeBase* NewGameMode)
{
	GameMode = static_cast<ASilentWaifuGameMode*>(NewGameMode);
	SetManagers();
	OnGameModeLoadedDelegate.Broadcast();
}


void USilentWaifuGameInstance::SetManagers()
{
	if (!GameMode) return;
	MoneyManager = GameMode->MoneyManager;
	CharactersManager = GameMode->CharactersManager;
}


void USilentWaifuGameInstance::LoadCharacters()
{
	if (!CharactersManager || !SaveGameInstance) return;
	for (const auto& Character : SaveGameInstance->GetCharacters())
	{
		CharactersManager->OnCharacterAddedDelegate.Broadcast(Character.Key, Character.Value);
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
	if (!SaveGameInstance || !CharactersManager) return;
	for (const auto& Character : CharactersManager->GetAvailableCharacters())
	{
		SaveGameInstance->SaveCharacter(Character.Key, Character.Value);
	}
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SlotName, 0);
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
	if (!MoneyManager || !SaveGameInstance) return;
	MoneyManager->SetMaxMoney(SaveGameInstance->GetMaxMoney());
	MoneyManager->IncreaseMoney(SaveGameInstance->GetCurrentMoney());
}


void USilentWaifuGameInstance::LoadPositions() const
{
	if (!CharactersManager || !SaveGameInstance) return;
	for (const auto& Position : SaveGameInstance->GetTakenPositions())
	{
		CharactersManager->AddTakenPosition(Position.Key, Position.Value);
	}
}


void USilentWaifuGameInstance::SavePositions()
{
	if (!SaveGameInstance || !CharactersManager) return;
	SaveGameInstance->SaveTakenPositions(CharactersManager->GetTakenPositions());
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SlotName, 0);
}


void USilentWaifuGameInstance::SaveShop()
{
	if (!SaveGameInstance || !CharactersManager) return;
	SaveGameInstance->SaveShop(CharactersManager->GetShopCharacters());
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SlotName, 0);
}


void USilentWaifuGameInstance::LoadShop() const
{
	if (!CharactersManager || !SaveGameInstance) return;
	CharactersManager->SetShopCharacters(SaveGameInstance->GetShop());
}