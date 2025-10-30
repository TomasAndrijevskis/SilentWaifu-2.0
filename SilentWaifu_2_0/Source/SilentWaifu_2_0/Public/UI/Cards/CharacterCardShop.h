
#pragma once

#include "CoreMinimal.h"
#include "CharacterCardBase.h"
#include "CharacterCardShop.generated.h"


class UImage;

UCLASS()
class SILENTWAIFU_2_0_API UCharacterCardShop : public UCharacterCardBase
{
	GENERATED_BODY()

public:

	void CreateLimitIncreaseCard();
	
protected:

	virtual void SetImage(UTexture2D* NewImage) override;
	
	virtual void Action() override;

private:

	UPROPERTY(meta = (BindWidget))
	UImage* Image_CardImage;

	UPROPERTY(EditAnywhere)
	UTexture2D* Image_LimitIncreaseImage;
};
