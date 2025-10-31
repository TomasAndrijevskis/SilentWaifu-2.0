
#pragma once

#include "CoreMinimal.h"
#include "UI/Cards/CardBase.h"
#include "LimitIncreaseCard.generated.h"


class UTextBlock;

UCLASS()
class SILENTWAIFU_2_0_API ULimitIncreaseCard : public UCardBase
{
	GENERATED_BODY()

public:

	
protected:

	virtual void SetImage(UTexture2D* NewImage) override;
	
	virtual void Action() override;
	
private:

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Image;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_Price;
	
	UPROPERTY(EditAnywhere)
	UTexture2D* Image_LimitIncreaseImage;
};
