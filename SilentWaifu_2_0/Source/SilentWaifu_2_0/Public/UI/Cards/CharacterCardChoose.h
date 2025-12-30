
#pragma once

#include "CoreMinimal.h"
#include "CharacterCard.h"
#include "CharacterCardChoose.generated.h"


UCLASS()
class SILENTWAIFU_2_0_API UCharacterCardChoose : public UCharacterCard
{
	GENERATED_BODY()

public:
	
	virtual void Init() override;
	
protected:

	virtual void SetImage(UTexture2D* NewImage) override;

	virtual void Action() override;

	virtual void ApplyCardBrushStyle(FSlateBrush& BrushStyle, UTexture2D* Image) override;
	
private:

	UFUNCTION()
	void HandleCardState();
};
