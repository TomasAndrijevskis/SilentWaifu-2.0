
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
	OnCharacterLoadedDelegate.AddDynamic(this, &ACharacterTemplate::EnableIncomeTimer);
	OnValuesUpdatedDelegate.AddDynamic(this, &ACharacterTemplate::SetMoney);
	WasPreviouslyOnScreenDelegate.AddDynamic(this, &ACharacterTemplate::HandleOfflineIncome);
}


void ACharacterTemplate::SetValues(const int NewId, const int NewLevel, const int NewTimeLeft)
{
	Id = NewId;
	Level = NewLevel;
	TimeLeft = NewTimeLeft;
	OnValuesUpdatedDelegate.Broadcast();
	AbilityComponent->OnCharacterIdRequestDelegate.Broadcast(Id);
}


void ACharacterTemplate::SetMoney()
{
	if (!CharacterRow) SetCharacterRow();
	MoneyPerMinute = CharacterRow->Numbers.CoinsPerLevel[Level-1] / 60;
	OnCharacterLoadedDelegate.Broadcast();
}


void ACharacterTemplate::SetCharacterRow()
{
	if (!CharacterDataTable) return;
	const FName RowName = FName(*FString::FromInt(Id));
	CharacterRow = CharacterDataTable->FindRow<FCharacterData>(RowName, TEXT("Find Character By Id"));
}


void ACharacterTemplate::HandleOfflineIncome(const bool WasOnScreen)
{
	if (!WasOnScreen || !GameMode) return;
	const FDateTime ShutdownTime = GameMode->GetShutdownTime();
	const FDateTime CurrentTime = FDateTime::Now();
	const FTimespan ElapsedTime = CurrentTime - ShutdownTime;
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
		const FDateTime FirstPayoutTime = ShutdownTime + FTimespan::FromSeconds(TimeLeft);
		IncreaseMoneyAtTime(FirstPayoutTime);
		ElapsedSeconds -= TimeLeft;
		const int AmountOfTimes = ElapsedSeconds / IncomeInterval;
		TimeLeft = IncomeInterval - (ElapsedSeconds % IncomeInterval);
		for (int i = 0; i < AmountOfTimes; i++) IncreaseMoneyAtTime(FirstPayoutTime + FTimespan::FromSeconds(i * IncomeInterval));
	}
}


void ACharacterTemplate::UpdateLevel(const int NewLevel)
{
	Level = NewLevel;
	OnValuesUpdatedDelegate.Broadcast();
}


void ACharacterTemplate::ActivateAbility()
{
	AbilityComponent->OnAbilityActivatedDelegate.Broadcast();
}


void ACharacterTemplate::EnableIncomeTimer()
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


void ACharacterTemplate::IncreaseMoneyAtTime(const FDateTime& Time) const
{
	if (!MoneyManager) return;
	MoneyManager->IncreaseMoney(MoneyPerMinute * GetMoneyMultiplier(Time));
}


int ACharacterTemplate::GetMoneyMultiplier(const FDateTime& Time) const
{
	return 1;
}


FCharacterData* ACharacterTemplate::GetCharacterRow() const
{
	return CharacterRow;
}


int ACharacterTemplate::GetMoneyPerMinute() const
{
	return MoneyPerMinute;
}


int ACharacterTemplate::GetMoneyPerHour() const
{
	return CharacterRow->Numbers.CoinsPerLevel[Level-1] * GetMoneyMultiplier(FDateTime::Now());
}


int ACharacterTemplate::GetId() const
{
	return Id;
}


float ACharacterTemplate::GetLeftTime() const
{
	return TimeLeft;
}
