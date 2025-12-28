
#include "Character/Abilities/AbilityComponent_Legendary.h"
#include "Character/CharacterTemplate.h"
#include "GameMode/Helpers/MoneyManager.h"
#include "Kismet/GameplayStatics.h"


void UAbilityComponent_Legendary::Action()
{
	if (!MoneyManager) return;
	TArray<AActor*> Characters;
	int OverallMoney = 0;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACharacterTemplate::StaticClass(), Characters);
	if (Characters.Num() == 0) return;
	for (const auto Character : Characters)
	{
		if (!IsValid(Character)) continue;
		OverallMoney += Cast<ACharacterTemplate>(Character)->GetMoneyPerHour() * 2;
	}
	UE_LOG(LogTemp, Warning, TEXT("OverallMoney: %i"), OverallMoney);
	MoneyManager->IncreaseMoney(OverallMoney);
}
