
#pragma once

#include "CoreMinimal.h"
#include "CardBase.h"
#include "LimitIncreaseCard.generated.h"


class UWidgetReferenceDataAsset;
class UTextBlock;

UCLASS()
class SILENTWAIFU_2_0_API ULimitIncreaseCard : public UCardBase
{
	GENERATED_BODY()

public:
	
	virtual void CreateCard() override;

	virtual void Init() override;
	
protected:

	virtual void SetImage(UTexture2D* NewImage) override;
	
	virtual void Action() override;

	UFUNCTION()
	virtual void SetPriceText(const FString& NewPriceText);

	UPROPERTY(EditAnywhere)
	UWidgetReferenceDataAsset* WidgetReferences;
	
private:

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Image;
	
	UPROPERTY(EditAnywhere)
	UTexture2D* Image_LimitIncreaseImage;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_Price;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_AdditionalInfo;
	
	UFUNCTION()
	void IncreaseLimit();

	UFUNCTION()
	void HandleCardState();

	UFUNCTION()
	void OpenAdditionalInfo();

	UFUNCTION()
	void CloseAdditionalInfo();
	
	int Price;
};
