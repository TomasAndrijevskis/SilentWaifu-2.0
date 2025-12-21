
#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterTemplate.h"
#include "RareCharacter.generated.h"


UCLASS()
class SILENTWAIFU_2_0_API ARareCharacter : public ACharacterTemplate
{
	GENERATED_BODY()

public:

	ARareCharacter();
	
private:

	UPROPERTY(EditAnywhere)
	UAbilityComponent_Base* AbilityComponent;
};
