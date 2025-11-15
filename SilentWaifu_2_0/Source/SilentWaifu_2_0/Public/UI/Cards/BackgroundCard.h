
#pragma once

#include "CoreMinimal.h"
#include "CardBase.h"
#include "BackgroundCard.generated.h"


class UWidgetReferenceDataAsset;
class UBackgroundManager;
class UTextBlock;

UCLASS()
class SILENTWAIFU_2_0_API UBackgroundCard : public UCardBase
{
	GENERATED_BODY()
	
public:
	
	void CreateCard(UTexture2D* NewImage, int BackgroundId, int NewPrice);

	virtual void Init() override;
	
protected:

	virtual void SetImage(UTexture2D* NewImage) override;
	
	virtual void Action() override;

	UPROPERTY(EditAnywhere)
	UWidgetReferenceDataAsset* WidgetReferences;
	
private:

	
	UPROPERTY(meta=(BindWidget))
	UBorder* Border;
	
	UPROPERTY()
	UBackgroundManager* BackgroundManager;
	
	bool IsBackgroundUnlocked();

	UFUNCTION()
	void RemoveOverviewWindow();
	
	UPROPERTY()
	UTexture2D* Image;
	
	int Id;

	int Price;
};
