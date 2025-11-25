
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LimitCardAdditionalInfo.generated.h"


class UTextBlock;
class UButton;
class UWidgetReferenceDataAsset;

UCLASS()
class SILENTWAIFU_2_0_API ULimitCardAdditionalInfo : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Close;

	void SetText(int Amount);

private:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_Amount;
};
