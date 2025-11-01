
#pragma once

#include "CoreMinimal.h"
#include "CharacterCard.h"
#include "CharacterCardMainScreen.generated.h"


class UWidgetReferenceDataAsset;
class UButton;

UCLASS()
class SILENTWAIFU_2_0_API UCharacterCardMainScreen : public UCharacterCard
{
	GENERATED_BODY()

public:
	
	virtual void CreateCard(const int Id) override;

protected:

	virtual void SetImage(UTexture2D* NewImage) override;
	
	virtual void Action() override;
	
};
