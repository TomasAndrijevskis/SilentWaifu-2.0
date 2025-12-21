
#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterTemplate.h"
#include "EventCharacter.generated.h"


UCLASS()
class SILENTWAIFU_2_0_API AEventCharacter : public ACharacterTemplate
{
	GENERATED_BODY()

public:

	AEventCharacter();
	
private:

	UPROPERTY(EditAnywhere)
	UAbilityComponent_Base* AbilityComponent;
};
