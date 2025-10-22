
#include "GameMode/SilentWaifuGameMode.h"
#include "Blueprint/UserWidget.h"
#include "Character/CharacterTemplate.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGame/SilentWaifuGameInstance.h"
#include "UI/MainScreen.h"


void ASilentWaifuGameMode::BeginPlay()
{
	Super::BeginPlay();
	OnCharacterAddedDelegate.AddDynamic(this, &ASilentWaifuGameMode::SetAvailableCharacters);
	OnCharactersLoadedDelegate.AddDynamic(this, &ASilentWaifuGameMode::SpawnCharacters);
	GameInstance = Cast<USilentWaifuGameInstance>(UGameplayStatics::GetGameInstance(this));
	if (!GameInstance)
	{
		return;
	}
	GameInstance->SetGameMode(this);
	CreateMainScreenWidget();
	SetInputSettings();
	GameInstance->LoadMoney();
	OnMoneyChangedDelegate.AddDynamic(GameInstance, &USilentWaifuGameInstance::SaveMoney);
}


void ASilentWaifuGameMode::CreateMainScreenWidget()
{
	if (MainScreenWidgetClass)
	{
		MainScreenWidgetRef = Cast<UMainScreen>(CreateWidget(GetWorld(), MainScreenWidgetClass));
		if (MainScreenWidgetRef)
		{
			MainScreenWidgetRef->AddToViewport(0);
		}
	}
}


void ASilentWaifuGameMode::SetInputSettings() const
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(),0);
	PC->SetShowMouseCursor(true);
	FInputModeUIOnly InputMode;
	PC->SetInputMode(InputMode);
}


void ASilentWaifuGameMode::SpawnCharacters()
{
	for (auto Character : GetAvailableCharacters())
	{
		FActorSpawnParameters SpawnParameters;
		GetWorld()->SpawnActor<ACharacterTemplate>(Character.Value.CharacterClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParameters);
		UE_LOG(LogTemp, Warning, TEXT("SpawnCharacter: %i"), Character.Key);
	}
}


void ASilentWaifuGameMode::IncreaseMoney(const int Money)
{
	CurrentMoney += Money;
	OnMoneyChangedDelegate.Broadcast(CurrentMoney);
}


void ASilentWaifuGameMode::DecreaseMoney(const int Money)
{
	CurrentMoney -= Money;
	OnMoneyChangedDelegate.Broadcast(CurrentMoney);
}


bool ASilentWaifuGameMode::HasEnoughMoney(const int Money) const
{
	if (CurrentMoney >= Money)
	{
		return true;
	}
	return false;
}


void ASilentWaifuGameMode::SetAvailableCharacters(int const Key, const FSavedCharactersData& Data)
{
	AvailableCharacters.Add(Key, Data);
}


TMap<int, FSavedCharactersData> ASilentWaifuGameMode::GetAvailableCharacters() const
{
	return AvailableCharacters;
}
