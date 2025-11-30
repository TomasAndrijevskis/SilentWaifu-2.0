
#include "GameMode/SilentWaifuGameMode.h"
#include "Blueprint/UserWidget.h"
#include "GameMode/Helpers/BackgroundManager.h"
#include "GameMode/Helpers/CharactersManager.h"
#include "GameMode/Helpers/MoneyManager.h"
#include "GameMode/Helpers/SoundManager.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGame/SilentWaifuGameInstance.h"
#include "UI/Screens/MainScreen.h"


void ASilentWaifuGameMode::BeginPlay()
{
	Super::BeginPlay();
	HandleManagers();
	OnCharactersLoadedDelegate.AddDynamic(CharactersManager, &UCharactersManager::SpawnCharacters);
	GameInstance = Cast<USilentWaifuGameInstance>(UGameplayStatics::GetGameInstance(this));
	HandleGameLoad();
}


void ASilentWaifuGameMode::HandleManagers()
{
	MoneyManager = NewObject<UMoneyManager>(this);
	CharactersManager = NewObject<UCharactersManager>(this);
	BackgroundManager = NewObject<UBackgroundManager>(this);
	SoundManager = NewObject<USoundManager>(this);
	if (!CharactersManager || !MoneyManager || !BackgroundManager || !SoundManager) return;
	if (!CharacterDataTable || !BackgroundDataTable) return;
	CharactersManager->Init(CharacterDataTable);
	BackgroundManager->Init(BackgroundDataTable);
	MoneyManager->Init(MoneyLimitsDataTable);
	SoundManager->Init(MusicMixModifier, SFXMixModifier, MusicClass, SFXClass);
}


void ASilentWaifuGameMode::HandleGameLoad()
{
	if (!GameInstance) return;
	GameInstance->SetGameMode(this);
	GameInstance->LoadPositions();
	CreateMainScreenWidget();
	SetInputSettings();
	GameInstance->LoadMoney();
	GameInstance->LoadShop();
	GameInstance->LoadBackgrounds();
	GameInstance->LoadShutdownTime();
	GameInstance->LoadSoundsVolume();
	MoneyManager->OnCurrentMoneyChangedDelegate.AddDynamic(GameInstance, &USilentWaifuGameInstance::SaveCurrentMoney);
	MoneyManager->OnLevelIncreasedDelegate.AddDynamic(GameInstance, &USilentWaifuGameInstance::SaveLimitLevel);
	OnShopCreatedDelegate.AddDynamic(GameInstance, &USilentWaifuGameInstance::SaveShop);
}


void ASilentWaifuGameMode::CreateMainScreenWidget()
{
	if (!WidgetReferences || !WidgetReferences->MainScreenClass) return;
	WidgetReferences->MainScreenRef = Cast<UMainScreen>(CreateWidget(GetWorld(), WidgetReferences->MainScreenClass));
	if (!WidgetReferences->MainScreenRef) return;
	WidgetReferences->MainScreenRef->AddToViewport(0);
}


void ASilentWaifuGameMode::SetInputSettings() const
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(),0);
	PC->SetShowMouseCursor(true);
	const FInputModeUIOnly InputMode;
	PC->SetInputMode(InputMode);
}


void ASilentWaifuGameMode::OnCharacterSpawned(const int CurrentSpawnPosition) const
{
	if (!WidgetReferences || !WidgetReferences->MainScreenRef) return;
	WidgetReferences->MainScreenRef->OnCharacterSpawnedDelegate.Broadcast(CurrentSpawnPosition);
}


void ASilentWaifuGameMode::OnCharacterRemovedDelegate(const int Position) const
{
	if (!WidgetReferences || !WidgetReferences->MainScreenRef) return;
	WidgetReferences->MainScreenRef->OnCharacterRemovedDelegate.Broadcast(Position);
}


FDateTime ASilentWaifuGameMode::GetShutdownTime() const
{
	return ShutdownTime;
}


void ASilentWaifuGameMode::SetShutdownTime(const FDateTime& NewLastJoinTime)
{
	ShutdownTime = NewLastJoinTime;	
}
