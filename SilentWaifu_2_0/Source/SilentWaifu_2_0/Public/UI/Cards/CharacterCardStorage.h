
#pragma once

#include "CoreMinimal.h"
#include "CharacterCard.h"
#include "CharacterCardStorage.generated.h"


class UWidgetReferenceDataAsset;

UCLASS()
class SILENTWAIFU_2_0_API UCharacterCardStorage : public UCharacterCard
{
	GENERATED_BODY()

protected:

	virtual void SetImage(UTexture2D* NewImage) override;
	
	virtual void Action() override;

	UPROPERTY(EditAnywhere)
	UWidgetReferenceDataAsset* WidgetReferences;
};
