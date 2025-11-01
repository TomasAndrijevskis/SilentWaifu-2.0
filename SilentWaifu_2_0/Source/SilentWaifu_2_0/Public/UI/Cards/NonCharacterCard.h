
#pragma once

#include "CoreMinimal.h"
#include "UI/Cards/CardBase.h"
#include "NonCharacterCard.generated.h"


UCLASS()
class SILENTWAIFU_2_0_API UNonCharacterCard : public UCardBase
{
	GENERATED_BODY()

		
public:
	
	virtual void CreateCard() override;

protected:

	UPROPERTY(EditAnywhere)
	UTexture2D* Image_LimitIncreaseImage;

};
