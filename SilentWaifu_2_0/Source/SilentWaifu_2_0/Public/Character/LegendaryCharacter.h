
#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterTemplate.h"
#include "LegendaryCharacter.generated.h"


UCLASS()
class SILENTWAIFU_2_0_API ALegendaryCharacter : public ACharacterTemplate
{
	GENERATED_BODY()

public:

	ALegendaryCharacter();
	
private:

	UPROPERTY(EditAnywhere)
	UAbilityComponent_Base* AbilityComponent;
	
};
