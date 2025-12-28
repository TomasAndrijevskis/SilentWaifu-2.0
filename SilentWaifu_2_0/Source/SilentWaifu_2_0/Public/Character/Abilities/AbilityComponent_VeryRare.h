
#pragma once

#include "CoreMinimal.h"
#include "Character/Abilities/AbilityComponent_Base.h"
#include "AbilityComponent_VeryRare.generated.h"


UCLASS()
class SILENTWAIFU_2_0_API UAbilityComponent_VeryRare : public UAbilityComponent_Base
{
	GENERATED_BODY()
	
protected:

	virtual void Action() override;
};
