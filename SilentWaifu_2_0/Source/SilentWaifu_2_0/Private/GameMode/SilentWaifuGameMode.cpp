
#include "GameMode/SilentWaifuGameMode.h"
#include "Blueprint/UserWidget.h"
#include "Character/CharacterTemplate.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGame/SilentWaifuGameInstance.h"
#include "UI/MainScreen.h"


void ASilentWaifuGameMode::BeginPlay()
{
	Super::BeginPlay();
	GameInstance = Cast<USilentWaifuGameInstance>(UGameplayStatics::GetGameInstance(this));
	if (!GameInstance)
	{
		return;
	}
	GameInstance->SetGameMode(this);
	CreateMainScreenWidget();
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


void ASilentWaifuGameMode::SpawnCharacters(const TSubclassOf<ACharacterTemplate>& CharacterClass)
{
	FActorSpawnParameters SpawnParameters;
	GetWorld()->SpawnActor<ACharacterTemplate>(CharacterClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParameters);
	UE_LOG(LogTemp, Warning, TEXT("SpawnCharacters"));
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