
#pragma once

#include "CoreMinimal.h"
#include "CardBase.h"
#include "BackgroundCard.generated.h"


class UBackgroundManager;
class UTextBlock;

UCLASS()
class SILENTWAIFU_2_0_API UBackgroundCard : public UCardBase
{
	GENERATED_BODY()
	
public:
	
	void CreateCard(UTexture2D* NewImage, int BackgroundId);

	virtual void Init() override;
	
protected:

	virtual void SetImage(UTexture2D* NewImage) override;
	
	virtual void Action() override;

private:

	UPROPERTY()
	UBackgroundManager* BackgroundManager;

	bool HandleState();
	
	int Id;
};
