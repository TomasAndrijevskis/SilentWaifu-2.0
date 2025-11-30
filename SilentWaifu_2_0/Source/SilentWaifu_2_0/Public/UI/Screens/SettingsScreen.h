
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SettingsScreen.generated.h"


class USoundManager;
class ASilentWaifuGameMode;
class USlider;
class UWidgetReferenceDataAsset;
class UButton;

UCLASS()
class SILENTWAIFU_2_0_API USettingsScreen : public UUserWidget
{
	GENERATED_BODY()

public:
	
	virtual void NativeConstruct() override;
	
private:

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Close;

	UPROPERTY(meta = (BindWidget))
	USlider* Slider_SFXSound;

	UPROPERTY(meta = (BindWidget))
	USlider* Slider_MusicSound;

	void BindDelegates();

	void SetInitialValues();
	
	UFUNCTION()
	void RemoveScreen();

	UFUNCTION()
	void SetMusicVolume(const float Value);

	UFUNCTION()
	void SetSFXVolume(const float Value);

	UPROPERTY(EditAnywhere)
	UWidgetReferenceDataAsset* WidgetReferences;

	UPROPERTY()
	ASilentWaifuGameMode* GameMode;

	UPROPERTY()
	USoundManager* SoundManager;
};
