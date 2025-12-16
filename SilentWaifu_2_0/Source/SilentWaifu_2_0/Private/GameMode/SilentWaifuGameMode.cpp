
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
	GameInstance = Cast<USilentWaifuGameInstance>(UGameplayStatics::GetGameInstance(this));
	OnCharactersLoadedDelegate.AddDynamic(GameInstance, &USilentWaifuGameInstance::LoadShutdownTime);
	OnCharactersLoadedDelegate.AddDynamic(CharactersManager, &UCharactersManager::SpawnCharacters);
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
	GameInstance->LoadShop();
	GameInstance->LoadBackgrounds();
	GameInstance->LoadSoundsVolume();
	GameInstance->LoadEventMoney();
	MoneyManager->OnLevelIncreasedDelegate.AddUniqueDynamic(GameInstance, &USilentWaifuGameInstance::SaveLimitLevel);
	MoneyManager->OnEventMoneyChangedDelegate.AddUniqueDynamic(GameInstance, &USilentWaifuGameInstance::SaveEventMoney);
	OnShopCreatedDelegate.AddUniqueDynamic(GameInstance, &USilentWaifuGameInstance::SaveShop);
	HandleEvent();
}


void ASilentWaifuGameMode::HandleEvent()
{
	FDateTime CurrentTime = FDateTime::Now();
	if (CurrentTime > EventEndTime)
	{
		MoneyManager->DecreaseEventMoney(MoneyManager->GetEventMoney());
		HasEventStartedDelegate.Broadcast(false);
		return;
	}
	if (CurrentTime < EventStartTime)
	{
		FTimespan TimeLeft = EventStartTime - CurrentTime;
		TimeLeftUntilEventStart = TimeLeft.GetTotalSeconds();
		GetWorld()->GetTimerManager().SetTimer(EventStartTimer, this, &ASilentWaifuGameMode::SetTimerUntilEventStarts, 1, true, 0);
		HasEventStartedDelegate.Broadcast(false);
		return;
	}
	GetWorld()->GetTimerManager().SetTimer(EventEndTimer, this, &ASilentWaifuGameMode::SetTimerUntilEventEnds, 1, true, 0);
	FTimespan TimeLeft = EventEndTime - CurrentTime;
	TimeLeftUntilEventEnd = TimeLeft.GetTotalSeconds();
	HasEventStartedDelegate.Broadcast(true);
}


void ASilentWaifuGameMode::SetTimerUntilEventStarts()
{
	if (TimeLeftUntilEventStart > 0) TimeLeftUntilEventStart--;
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(EventStartTimer);
		HasEventStartedDelegate.Broadcast(true);
		OnEventStartedDelegate.Broadcast(EventEndTime);
	}
}


void ASilentWaifuGameMode::SetTimerUntilEventEnds()
{
	if (TimeLeftUntilEventEnd > 0) TimeLeftUntilEventEnd--;
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(EventEndTimer);
		HasEventStartedDelegate.Broadcast(false);
		OnEventEndedDelegate.Broadcast();
	}
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


FDateTime ASilentWaifuGameMode::GetEventEndTime() const
{
	return EventEndTime;
}