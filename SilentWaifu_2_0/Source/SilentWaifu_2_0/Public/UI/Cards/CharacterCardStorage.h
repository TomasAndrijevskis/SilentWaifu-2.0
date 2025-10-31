
#pragma once

#include "CoreMinimal.h"
#include "CardBase.h"
#include "CharacterCardStorage.generated.h"


UCLASS()
class SILENTWAIFU_2_0_API UCharacterCardStorage : public UCardBase
{
	GENERATED_BODY()

protected:

	virtual void SetImage(UTexture2D* NewImage) override;
	
	virtual void Action() override;
};
