
#pragma once

#include "CoreMinimal.h"
#include "Character/Abilities/AbilityComponent_Base.h"
#include "AbilityComponent_Elite.generated.h"


UCLASS()
class SILENTWAIFU_2_0_API UAbilityComponent_Elite : public UAbilityComponent_Base
{
	GENERATED_BODY()

protected:
	
	virtual void Action() override;

private:

	int RoundDigits(const int CurrentMoney) const;
};
