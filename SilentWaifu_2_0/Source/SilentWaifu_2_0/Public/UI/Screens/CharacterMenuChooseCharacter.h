
#pragma once

#include "CoreMinimal.h"
#include "UI/Screens/CharacterMenuBase.h"
#include "CharacterMenuChooseCharacter.generated.h"


UCLASS()
class SILENTWAIFU_2_0_API UCharacterMenuChooseCharacter : public UCharacterMenuBase
{
	GENERATED_BODY()

public:

	virtual void RemoveCharacterMenu() override;
	
protected:

	virtual void CreateCharacterMenu() override;
	
};
