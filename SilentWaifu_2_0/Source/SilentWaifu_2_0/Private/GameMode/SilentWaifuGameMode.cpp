
#include "GameMode/SilentWaifuGameMode.h"
#include "Character/CharacterTemplate.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGame/SilentWaifuGameInstance.h"


void ASilentWaifuGameMode::BeginPlay()
{
	Super::BeginPlay();
	GameInstance = Cast<USilentWaifuGameInstance>(UGameplayStatics::GetGameInstance(this));
	if (!GameInstance)
	{
		return;
	}
	GameInstance->SetGameMode(this);
	GameInstance->LoadMoney();
	OnMoneyChangedDelegate.AddDynamic(this, &ASilentWaifuGameMode::ShowMoney);
}


void ASilentWaifuGameMode::SpawnCharacters(const TSubclassOf<ACharacterTemplate>& CharacterClass)
{
	FActorSpawnParameters SpawnParameters;
	GetWorld()->SpawnActor<ACharacterTemplate>(CharacterClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParameters);
	UE_LOG(LogTemp, Warning, TEXT("SpawnCharacters"));
}


void ASilentWaifuGameMode::ShowMoney()
{
	UE_LOG(LogTemp, Warning, TEXT("ShowMoney: %i"), CurrentMoney);
	GameInstance->SaveMoney(CurrentMoney);
}


void ASilentWaifuGameMode::IncreaseMoney(const int Money)
{
	CurrentMoney += Money;
	OnMoneyChangedDelegate.Broadcast();
}


void ASilentWaifuGameMode::DecreaseMoney(const int Money)
{
	CurrentMoney -= Money;
	OnMoneyChangedDelegate.Broadcast();
}