
#include "Character/Abilities/AbilityComponent_Rare.h"
#include "Character/CharacterTemplate.h"
#include "GameMode/Helpers/MoneyManager.h"


void UAbilityComponent_Rare::Action()
{	
	if (!MoneyManager || !CharacterRef) return;
	if (FMath::RandRange(0,1) == 0) MoneyManager->IncreaseMoney(CharacterRef->GetMoneyPerHour() * 2);
	else UE_LOG(LogTemp, Warning, TEXT("Unlucky"));
}
