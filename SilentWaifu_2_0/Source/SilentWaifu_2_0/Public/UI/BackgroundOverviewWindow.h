
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BackgroundOverviewWindow.generated.h"


class UBackgroundManager;
class UTextBlock;
class UBackgroundBlur;
class UImage;
class UButton;

UCLASS()
class SILENTWAIFU_2_0_API UBackgroundOverviewWindow : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Close;

	void Init(UTexture2D* NewImage, int Price, int NewId, const bool IsUnlocked, UBackgroundManager* NewBackgroundManager);
	
private:

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Action;

	UPROPERTY(meta = (BindWidget))
	UImage* Image_Background;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_InputBlocker;

	UPROPERTY(meta=(BindWidget))
	UBackgroundBlur* Blur;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Text_ActionText;

	UFUNCTION()
	void Unlock();

	UFUNCTION()
	void Set();
	
	void SetImage(UTexture2D* NewImage);

	void SetButtonText(const FString& Text);

	UPROPERTY()
	UBackgroundManager* BackgroundManager;
	
	UPROPERTY()
	UTexture2D* Image;

	UPROPERTY()
	int Id;
};
