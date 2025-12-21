
#include "Character/CharacterTemplate.h"
#include "TimerManager.h"
#include "Character/Abilities/AbilityComponent_Base.h"
#include "DataTables/CharacterData.h"
#include "Engine/World.h"
#include "GameMode/SilentWaifuGameMode.h"
#include "GameMode/Helpers/CharactersManager.h"
#include "GameMode/Helpers/MoneyManager.h"
#include "Kismet/GameplayStatics.h"


void ACharacterTemplate::BeginPlay()
{
	Super::BeginPlay();
	GameMode = Cast<ASilentWaifuGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!GameMode) return;
	MoneyManager = GameMode->MoneyManager;
	CharactersManager = GameMode->CharactersManager;
	if (!MoneyManager || !CharactersManager) return;
	OnCharacterLoadedDelegate.AddDynamic(this, &ACharacterTemplate::EnableTimer);
	OnValuesUpdatedDelegate.AddDynamic(this, &ACharacterTemplate::SetMoney);
	WasPreviouslyOnScreenDelegate.AddDynamic(this, &ACharacterTemplate::HandleOfflineIncome);
}


void ACharacterTemplate::SetValues(const int NewId, const int NewLevel, const int NewTimeLeft)
{
	Id = NewId;
	Level = NewLevel;
	TimeLeft = NewTimeLeft;
	OnValuesUpdatedDelegate.Broadcast();
}


void ACharacterTemplate::SetMoney()
{
	if (!CharacterRow) GetCharacterRow();
	MoneyPerMinute = CharacterRow->Numbers.CoinsPerLevel[Level-1] / 60;
	OnCharacterLoadedDelegate.Broadcast();
}


void ACharacterTemplate::GetCharacterRow()
{
	if (!CharacterDataTable) return;
	const FName RowName = FName(*FString::FromInt(Id));
	CharacterRow = CharacterDataTable->FindRow<FCharacterData>(RowName, TEXT("Find Character By Id"));
}


void ACharacterTemplate::HandleOfflineIncome(const bool WasOnScreen)
{
	if (!WasOnScreen || !GameMode) return;
	FDateTime ShutdownTime = GameMode->GetShutdownTime();
	FDateTime CurrentTime = FDateTime::Now();
	FTimespan ElapsedTime = CurrentTime - ShutdownTime;
	int ElapsedSeconds = ElapsedTime.GetTotalSeconds();
	if (ElapsedSeconds == TimeLeft)
	{
		IncreaseMoney();
		TimeLeft = IncomeInterval;
		return;
	}
	if (ElapsedSeconds < TimeLeft)
	{
		TimeLeft -= ElapsedSeconds;
		return;
	}
	if (ElapsedSeconds > TimeLeft)
	{
		IncreaseMoney();
		ElapsedSeconds -= TimeLeft;
		int AmountOfTimes = ElapsedSeconds / IncomeInterval;
		TimeLeft = IncomeInterval - (ElapsedSeconds % IncomeInterval);
		for (int i = 0; i < AmountOfTimes; i++) IncreaseMoney();
	}
}


void ACharacterTemplate::UpdateLevel(const int NewLevel)
{
	Level = NewLevel;
	OnValuesUpdatedDelegate.Broadcast();
}


void ACharacterTemplate::EnableTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ACharacterTemplate::CheckTime, 1, true);
}


void ACharacterTemplate::CheckTime()
{
	if (TimeLeft != 0) TimeLeft--;
	else
	{
		IncreaseMoney();
		TimeLeft = IncomeInterval;
	}
}


void ACharacterTemplate::IncreaseMoney() const
{
	if (!MoneyManager) return;
	MoneyManager->IncreaseMoney(MoneyPerMinute);
}


int ACharacterTemplate::GetMoneyPerMinute() const
{
	return MoneyPerMinute;
}


int ACharacterTemplate::GetMoneyPerHour() const
{
	return  CharacterRow->Numbers.CoinsPerLevel[Level-1];
}


int ACharacterTemplate::GetId() const
{
	return Id;
}


float ACharacterTemplate::GetLeftTime() const
{
	return TimeLeft;
}
