
#include "Character/CharacterTemplate.h"
#include "TimerManager.h"
#include "DataTables/CharacterData.h"
#include "Engine/World.h"
#include "GameMode/SilentWaifuGameMode.h"
#include "Kismet/GameplayStatics.h"


void ACharacterTemplate::BeginPlay()
{
	Super::BeginPlay();
	GameMode = Cast<ASilentWaifuGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!GameMode) return;
	OnCharacterLoadedDelegate.AddDynamic(this, &ACharacterTemplate::EnableTimer);
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
	SetMoney();
}


void ACharacterTemplate::UpdateLevel(const int NewLevel)
{
	Level = NewLevel;
	SetMoney();
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
	UE_LOG(LogTemp, Warning, TEXT("IncreaseMoney"));
	GameMode->IncreaseMoney(MoneyPerSecond);
}
