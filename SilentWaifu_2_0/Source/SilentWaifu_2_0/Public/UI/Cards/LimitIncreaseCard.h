
#pragma once

#include "CoreMinimal.h"
#include "NonCharacterCard.h"
#include "LimitIncreaseCard.generated.h"


class UTextBlock;

UCLASS()
class SILENTWAIFU_2_0_API ULimitIncreaseCard : public UNonCharacterCard
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;
	
protected:

	virtual void SetImage(UTexture2D* NewImage) override;
	
	virtual void Action() override;
	
private:

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Image;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_Price;

	UFUNCTION()
	void SetPriceText();
	
	int Price = 100;
};
