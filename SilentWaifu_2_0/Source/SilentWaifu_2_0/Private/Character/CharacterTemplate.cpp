
#include "Character/CharacterTemplate.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "GameMode/SilentWaifuGameMode.h"
#include "Kismet/GameplayStatics.h"


void ACharacterTemplate::BeginPlay()
{
	Super::BeginPlay();
	GameMode = Cast<ASilentWaifuGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!GameMode)
	{
		return;
	}
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ACharacterTemplate::IncreaseMoney, 1.f, true);
}


void ACharacterTemplate::IncreaseMoney() const
{
	GameMode->IncreaseMoney(MoneyPerSecond);
	
}