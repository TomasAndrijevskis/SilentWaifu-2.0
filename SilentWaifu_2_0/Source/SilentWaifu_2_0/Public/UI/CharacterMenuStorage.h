
#pragma once

#include "CoreMinimal.h"
#include "UI/CharacterMenuBase.h"
#include "CharacterMenuStorage.generated.h"

UCLASS()
class SILENTWAIFU_2_0_API UCharacterMenuStorage : public UCharacterMenuBase
{
	GENERATED_BODY()

protected:

	virtual void CreateCharacterMenu() override;
	
};
