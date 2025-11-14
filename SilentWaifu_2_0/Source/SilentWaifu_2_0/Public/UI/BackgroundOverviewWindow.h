
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

	void Init(UTexture2D* NewImage, int NewPrice, int NewId, const bool IsUnlocked, UBackgroundManager* NewBackgroundManager);

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
	void UnlockBackground();

	UFUNCTION()
	void SetBackground();
	
	void SetImage(UTexture2D* NewImage);

	void SetButtonText(const FString& Text);

	void SetInitialValues(int NewId, int NewPrice, UBackgroundManager* NewBackgroundManager);

	void HandleActionButton(const bool IsUnlocked);
	
	UPROPERTY()
	UBackgroundManager* BackgroundManager;
	
	UPROPERTY()
	UTexture2D* Image;

	int Id;
	
	int Price;
};

