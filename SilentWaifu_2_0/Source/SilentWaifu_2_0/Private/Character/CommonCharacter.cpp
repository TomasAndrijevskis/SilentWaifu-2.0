
#include "Character/CommonCharacter.h"
#include "Character/Abilities/AbilityComponent_Base.h"
#include "Character/Abilities/AbilityComponent_Common.h"
#include "GameMode/Helpers/CharactersManager.h"
#include "SaveGame/SavedCharactersData.h"


ACommonCharacter::ACommonCharacter()
{
	AbilityComponent = CreateDefaultSubobject<UAbilityComponent_Common>(TEXT("Ability Component"));
}


int ACommonCharacter::GetMoneyMultiplier(const FDateTime& Time) const
{
	if (!CharactersManager) return 1;
	if (!WasAbilityUsed()) return 1;
	if (GetAbilityUsageTime() <= Time && Time < GetAbilityEndTime()) return MoneyMultiplier;
	return 1;
}


FDateTime ACommonCharacter::GetAbilityEndTime() const
{
	FSavedCharactersData* Data = CharactersManager->GetAvailableCharacters().Find(GetId());
	if (!Data) return 0;
	int Duration = Cast<UAbilityComponent_Common>(AbilityComponent)->GetAbilityDuration();
	const FDateTime AbilityUsageTime = Data->AbilityData.UsageTime;
	return AbilityUsageTime + FTimespan::FromHours(Duration);
}


FDateTime ACommonCharacter::GetAbilityUsageTime() const
{
	FSavedCharactersData* Data = CharactersManager->GetAvailableCharacters().Find(GetId());
	if (!Data) return 0;
	return Data->AbilityData.UsageTime;
}


bool ACommonCharacter::WasAbilityUsed() const
{
	return CharactersManager->GetAvailableCharacters().Find(GetId())->AbilityData.WasAbilityUsed;
}
