
#pragma once

#include "CoreMinimal.h"
#include "UI/CharacterMenuBase.h"
#include "CharacterMenuChooseCharacter.generated.h"


UCLASS()
class SILENTWAIFU_2_0_API UCharacterMenuChooseCharacter : public UCharacterMenuBase
{
	GENERATED_BODY()
	
protected:

	virtual void CreateCharacterMenu() override;
	
};
