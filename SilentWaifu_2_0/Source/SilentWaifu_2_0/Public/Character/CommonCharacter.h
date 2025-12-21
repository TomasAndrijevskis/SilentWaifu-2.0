
#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterTemplate.h"
#include "CommonCharacter.generated.h"


UCLASS()
class SILENTWAIFU_2_0_API ACommonCharacter : public ACharacterTemplate
{
	GENERATED_BODY()

public:

	ACommonCharacter();
	
private:

	UPROPERTY(EditAnywhere)
	UAbilityComponent_Base* AbilityComponent;
};
