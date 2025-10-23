
#pragma once

#include "CoreMinimal.h"
#include "UI/CharacterCardBase.h"
#include "CharacterCardStorage.generated.h"


UCLASS()
class SILENTWAIFU_2_0_API UCharacterCardStorage : public UCharacterCardBase
{
	GENERATED_BODY()

protected:

	virtual void SetImage(UTexture2D* NewImage) override;
	
	virtual void Action() override;
};
