
#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterTemplate.h"
#include "EliteCharacter.generated.h"


UCLASS()
class SILENTWAIFU_2_0_API AEliteCharacter : public ACharacterTemplate
{
	GENERATED_BODY()

public:

	AEliteCharacter();
	
private:

	UPROPERTY(EditAnywhere)
	UAbilityComponent_Base* AbilityComponent;
};
