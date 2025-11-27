
#pragma once

#include "CoreMinimal.h"
#include "UI/Screens/CharacterMenuBase.h"
#include "CharacterMenuStorage.generated.h"

UCLASS()
class SILENTWAIFU_2_0_API UCharacterMenuStorage : public UCharacterMenuBase
{
	GENERATED_BODY()

protected:

	virtual void CreateCharacterMenu() override;
	
	virtual void RemoveCharacterMenu() override;
};
