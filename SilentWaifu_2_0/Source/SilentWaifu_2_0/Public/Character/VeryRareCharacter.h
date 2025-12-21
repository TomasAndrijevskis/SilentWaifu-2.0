
#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterTemplate.h"
#include "VeryRareCharacter.generated.h"


UCLASS()
class SILENTWAIFU_2_0_API AVeryRareCharacter : public ACharacterTemplate
{
	GENERATED_BODY()

	
public:

	AVeryRareCharacter();
	
private:

	UPROPERTY(EditAnywhere)
	UAbilityComponent_Base* AbilityComponent;
};
