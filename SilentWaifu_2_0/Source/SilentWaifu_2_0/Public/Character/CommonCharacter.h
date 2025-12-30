
#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterTemplate.h"
#include "SaveGame/SavedCharactersData.h"
#include "CommonCharacter.generated.h"


UCLASS()
class SILENTWAIFU_2_0_API ACommonCharacter : public ACharacterTemplate
{
	GENERATED_BODY()

public:

	ACommonCharacter();
	
protected:

	virtual int GetMoneyMultiplier(const FDateTime& Time) const override;
	
private:

	FDateTime GetAbilityEndTime() const;

	FDateTime GetAbilityUsageTime() const;
	
	bool WasAbilityUsed() const;
	
	int MoneyMultiplier = 2;
};
