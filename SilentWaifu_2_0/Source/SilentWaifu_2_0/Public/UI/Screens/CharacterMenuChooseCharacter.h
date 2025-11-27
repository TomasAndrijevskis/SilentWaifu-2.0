
#pragma once

#include "CoreMinimal.h"
#include "UI/Screens/CharacterMenuBase.h"
#include "CharacterMenuChooseCharacter.generated.h"


UCLASS()
class SILENTWAIFU_2_0_API UCharacterMenuChooseCharacter : public UCharacterMenuBase
{
	GENERATED_BODY()

protected:

	virtual void CreateCharacterMenu() override;
	
	virtual void RemoveCharacterMenu() override;
};
