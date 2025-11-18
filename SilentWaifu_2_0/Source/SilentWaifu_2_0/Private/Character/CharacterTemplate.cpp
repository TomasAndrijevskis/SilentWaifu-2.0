
#include "Character/CharacterTemplate.h"
#include "TimerManager.h"
#include "DataTables/CharacterData.h"
#include "Engine/World.h"
#include "GameMode/SilentWaifuGameMode.h"
#include "GameMode/Helpers/MoneyManager.h"
#include "Kismet/GameplayStatics.h"


void ACharacterTemplate::BeginPlay()
{
	Super::BeginPlay();
	GameMode = Cast<ASilentWaifuGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!GameMode) return;
	MoneyManager = GameMode->MoneyManager;
	OnCharacterLoadedDelegate.AddDynamic(this, &ACharacterTemplate::EnableTimer);
	OnValuesUpdatedDelegate.AddDynamic(this, &ACharacterTemplate::SetMoney);
}


void ACharacterTemplate::SetMoney()
{
	if (!CharacterRow) GetCharacterRow();
	MoneyPerSecond = CharacterRow->Numbers.CoinsPerLevel[Level-1];
	OnCharacterLoadedDelegate.Broadcast();
}


void ACharacterTemplate::SetValues(const int NewLevel, const int NewId)
{
	Level = NewLevel;
	Id = NewId;
	OnValuesUpdatedDelegate.Broadcast();
}


void ACharacterTemplate::UpdateLevel(const int NewLevel)
{
	Level = NewLevel;
	OnValuesUpdatedDelegate.Broadcast();
}


void ACharacterTemplate::EnableTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ACharacterTemplate::IncreaseMoney, 2.f, true);
}


void ACharacterTemplate::GetCharacterRow()
{
	if (!CharacterDataTable) return;
	const FName RowName = FName(*FString::FromInt(Id));
	CharacterRow = CharacterDataTable->FindRow<FCharacterData>(RowName, TEXT("Find Character By Id"));
}


void ACharacterTemplate::IncreaseMoney() const
{
	if (!MoneyManager) return;
	MoneyManager->IncreaseMoney(MoneyPerSecond);
}


int ACharacterTemplate::GetMoneyPerSecond() const
{
	return MoneyPerSecond;
}