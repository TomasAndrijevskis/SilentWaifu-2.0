
#pragma once

#include "CoreMinimal.h"
#include "Character/Abilities/AbilityComponent_Base.h"
#include "AbilityComponent_Common.generated.h"


UCLASS()
class SILENTWAIFU_2_0_API UAbilityComponent_Common : public UAbilityComponent_Base
{
	GENERATED_BODY()

public:

	int GetAbilityDuration() const;
	
protected:

	virtual void Action() override;

private:

	int DurationHours = 2;
};
