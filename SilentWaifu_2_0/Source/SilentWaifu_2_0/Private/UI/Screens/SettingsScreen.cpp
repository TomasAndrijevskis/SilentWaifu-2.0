
#include "UI/Screens/SettingsScreen.h"
#include "Components/Button.h"
#include "Components/Slider.h"
#include "GameMode/SilentWaifuGameMode.h"
#include "GameMode/Helpers/SoundManager.h"
#include "Kismet/GameplayStatics.h"
#include "UI/WidgetReferenceDataAsset.h"


void USettingsScreen::NativeConstruct()
{
	Super::NativeConstruct();
	GameMode = Cast<ASilentWaifuGameMode>(UGameplayStatics::GetGameMode(this));
	if (!GameMode) return;
	SoundManager = GameMode->SoundManager;
	if (!SoundManager) return;
	BindDelegates();
	SetInitialValues();
}


void USettingsScreen::BindDelegates()
{
	Button_Close->OnClicked.AddDynamic(this, &USettingsScreen::RemoveScreen);
	Slider_MusicSound->OnValueChanged.AddUniqueDynamic(this, &USettingsScreen::SetMusicVolume);
	Slider_SFXSound->OnValueChanged.AddUniqueDynamic(this, &USettingsScreen::SetSFXVolume);
}


void USettingsScreen::SetInitialValues()
{
	if (!SoundManager) return;
	Slider_MusicSound->SetValue(SoundManager->GetMusicVolume());
	Slider_SFXSound->SetValue(SoundManager->GetSFXVolume());
}


void USettingsScreen::RemoveScreen()
{
	if (!WidgetReferences || !WidgetReferences->SettingsScreenRef) return;
	WidgetReferences->SettingsScreenRef->RemoveFromParent();
	WidgetReferences->SettingsScreenRef = nullptr;
}


void USettingsScreen::SetMusicVolume(const float Value)
{
	if (!SoundManager) return;
	SoundManager->SetMusicVolume(Value);
}


void USettingsScreen::SetSFXVolume(const float Value)
{
	if (!SoundManager) return;
	SoundManager->SetSFXVolume(Value);
}
