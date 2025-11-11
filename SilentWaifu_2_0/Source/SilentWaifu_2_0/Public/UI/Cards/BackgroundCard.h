
#pragma once

#include "CoreMinimal.h"
#include "CardBase.h"
#include "BackgroundCard.generated.h"


class UTextBlock;

UCLASS()
class SILENTWAIFU_2_0_API UBackgroundCard : public UCardBase
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;

	void CreateCard(UTexture2D* NewImage);
	
protected:

	virtual void SetImage(UTexture2D* NewImage) override;
	
	virtual void Action() override;
};
