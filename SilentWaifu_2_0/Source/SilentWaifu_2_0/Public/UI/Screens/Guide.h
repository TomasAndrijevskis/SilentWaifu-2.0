
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Guide.generated.h"


class UImage;
class UButton;

UCLASS()
class SILENTWAIFU_2_0_API UGuide : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

private:

	UPROPERTY(meta=(BindWidget))
	UButton* Button_Next;

	UPROPERTY(meta=(BindWidget))
	UButton* Button_Previous;

	UPROPERTY(meta=(BindWidget))
	UButton* Button_Skip;

	UPROPERTY(meta=(BindWidget))
	UImage* Image_Character;

	UPROPERTY(meta=(BindWidget))
	UImage* Image_Guide;

	UFUNCTION()
	void NextImage();

	UFUNCTION()
	void PreviousImage();

	UFUNCTION()
	void RemoveGuide();

	UFUNCTION()
	void RebindActions(bool IsLastImage);
	
	void SetGuideImage();

	void HandleButtons();
	
	UPROPERTY(EditAnywhere)
	TArray<UTexture2D*> GuideImages;

	int CurrentGuideIndex = 0;
};
