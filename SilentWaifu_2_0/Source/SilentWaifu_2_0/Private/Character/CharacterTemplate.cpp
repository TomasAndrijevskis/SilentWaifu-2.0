
#include "Character/CharacterTemplate.h"
#include "TimerManager.h"
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
}


void ACharacterTemplate::SetValues(const int NewId, const int NewLevel, const float TimeLeft)
{
	Id = NewId;
	Level = NewLevel;
	IncomeInterval = TimeLeft;
	OnValuesUpdatedDelegate.Broadcast();
}


void ACharacterTemplate::SetMoney()
{
	if (!CharacterRow) GetCharacterRow();
	MoneyPerSecond = CharacterRow->Numbers.CoinsPerLevel[Level-1];
	OnCharacterLoadedDelegate.Broadcast();
}


void ACharacterTemplate::GetCharacterRow()
{
	if (!CharacterDataTable) return;
	const FName RowName = FName(*FString::FromInt(Id));
	CharacterRow = CharacterDataTable->FindRow<FCharacterData>(RowName, TEXT("Find Character By Id"));
}


void ACharacterTemplate::UpdateLevel(const int NewLevel)
{
	Level = NewLevel;
	OnValuesUpdatedDelegate.Broadcast();
}


void ACharacterTemplate::EnableTimer()
{
	TempTime = IncomeInterval;
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ACharacterTemplate::CheckTime, 1, true);
}


void ACharacterTemplate::CheckTime()
{
	if (TempTime != 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Time left: %f"), TempTime);
		TempTime --;
	}
	else
	{
		IncreaseMoney();
		if (IncomeInterval != 10) IncomeInterval = 10;
		TempTime = IncomeInterval;
	}
}


void ACharacterTemplate::IncreaseMoney()
{
	if (!MoneyManager) return;
	MoneyManager->IncreaseMoney(MoneyPerSecond);
}


int ACharacterTemplate::GetMoneyPerSecond() const
{
	return MoneyPerSecond;
}


int ACharacterTemplate::GetId() const
{
	return Id;
}


float ACharacterTemplate::GetLeftTime() const
{
	return TempTime;
}
