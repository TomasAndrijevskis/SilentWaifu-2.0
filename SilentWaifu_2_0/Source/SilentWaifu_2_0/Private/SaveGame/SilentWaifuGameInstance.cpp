
#include "SaveGame/SilentWaifuGameInstance.h"
#include "GameMode/SilentWaifuGameMode.h"
#include "GameMode/Helpers/BackgroundManager.h"
#include "GameMode/Helpers/CharactersManager.h"
#include "GameMode/Helpers/MoneyManager.h"
#include "GameMode/Helpers/SoundManager.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGame/SilentWaifuSaveGame.h"


void USilentWaifuGameInstance::Init()
{
	Super::Init();
	HandleSaveGame();
	OnGameModeLoadedDelegate.AddDynamic(this, &USilentWaifuGameInstance::LoadLimitLevel);
	OnGameModeLoadedDelegate.AddDynamic(this, &USilentWaifuGameInstance::LoadCharacters);
}


void USilentWaifuGameInstance::Shutdown()
{
	SavePositions();
	SaveCharacters();
	SaveShop();
	SaveBackgrounds();
	SaveShutdownTime();
	SaveSoundsVolume();
	Super::Shutdown();
}


void USilentWaifuGameInstance::HandleSaveGame()
{
	SaveGameInstance = Cast<USilentWaifuSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));
	if (!SaveGameInstance)
	{
		SaveGameInstance = Cast<USilentWaifuSaveGame>(UGameplayStatics::CreateSaveGameObject(USilentWaifuSaveGame::StaticClass()));
		SetDefaultValues();
	}
}


void USilentWaifuGameInstance::SetDefaultValues()
{
	FSavedCharactersData Data;
	Data.CharacterClass = DefaultCharacter;
	Data.bIsOnScreen = false;
	Data.CharacterId = 1;
	Data.Level = 1;
	Data.TimeLeft = 10;
	SaveFirstCharacter(1, Data);
	SaveLimitLevel(1);
	SaveGameInstance->SaveSoundsVolume(0,0);
	
	FSavedBackgroundsData BackgroundData;
	BackgroundData.Id = 1;
	BackgroundData.IsActive = true;
	TArray<FSavedBackgroundsData> Backgrounds;
	Backgrounds.Add(BackgroundData);
	SaveGameInstance->SaveUnlockedBackgrounds(Backgrounds);
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
	BackgroundManager = GameMode->BackgroundManager;
	SoundManager = GameMode->SoundManager;
}


void USilentWaifuGameInstance::LoadCharacters()
{
	if (!SaveGameInstance || !CharactersManager) return;
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
	CharactersManager->SaveCharactersLeftTime();
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


void USilentWaifuGameInstance::LoadMoney() const
{
	if (!SaveGameInstance || !MoneyManager) return;
	MoneyManager->IncreaseMoney(SaveGameInstance->GetCurrentMoney());
}


void USilentWaifuGameInstance::LoadPositions() const
{
	if (!SaveGameInstance || !CharactersManager) return;
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
	if (!SaveGameInstance || !CharactersManager) return;
	CharactersManager->SetShopCharacters(SaveGameInstance->GetShop());
}


void USilentWaifuGameInstance::SaveBackgrounds()
{
	if (!SaveGameInstance || !BackgroundManager) return;
	SaveGameInstance->SaveUnlockedBackgrounds(BackgroundManager->GetUnlockedBackgrounds());
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SlotName, 0);
}


void USilentWaifuGameInstance::LoadBackgrounds()
{
	if (!SaveGameInstance || !BackgroundManager) return;
	BackgroundManager->SetUnlockedBackgrounds(SaveGameInstance->GetUnlockedBackgrounds());
}


void USilentWaifuGameInstance::SaveLimitLevel(const int Level)
{
	if (!SaveGameInstance) return;
	SaveGameInstance->SaveLimitLevel(Level);
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SlotName, 0);
}


void USilentWaifuGameInstance::LoadLimitLevel()
{
	if (!SaveGameInstance || !MoneyManager) return;
	MoneyManager->SetMoneyLimitLevel(SaveGameInstance->GetLimitLevel());
}


void USilentWaifuGameInstance::SaveShutdownTime()
{
	if (!SaveGameInstance) return;
	FDateTime CurrentTime = FDateTime::Now();
	SaveGameInstance->SaveShutdownTime(CurrentTime);
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SlotName, 0);
}


void USilentWaifuGameInstance::LoadShutdownTime()
{
	if (!SaveGameInstance) return;
	GameMode->SetShutdownTime(SaveGameInstance->GetShutdownTime());
	UE_LOG(LogTemp, Warning, TEXT("Loading time: %s"), *SaveGameInstance->GetShutdownTime().ToString());
}


void USilentWaifuGameInstance::SaveSoundsVolume() const
{
	if (!SaveGameInstance || !SoundManager) return;
	SaveGameInstance->SaveSoundsVolume(SoundManager->GetMusicVolume(), SoundManager->GetSFXVolume());
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SlotName, 0);
}


void USilentWaifuGameInstance::LoadSoundsVolume()
{
	if (!SaveGameInstance || !SoundManager) return;
	SoundManager->SetMusicVolume(SaveGameInstance->GetMusicVolume());
	SoundManager->SetSFXVolume(SaveGameInstance->GetSFXVolume());
}
