
#pragma once

#include "CoreMinimal.h"
#include "Character/Abilities/AbilityComponent_Base.h"
#include "AbilityComponent_Event.generated.h"


UCLASS()
class SILENTWAIFU_2_0_API UAbilityComponent_Event : public UAbilityComponent_Base
{
	GENERATED_BODY()

protected:

	virtual void Action() override;
};
