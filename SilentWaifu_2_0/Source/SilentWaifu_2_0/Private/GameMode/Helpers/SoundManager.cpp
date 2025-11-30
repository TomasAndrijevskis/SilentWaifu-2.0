
#include "GameMode/Helpers/SoundManager.h"
#include "Kismet/GameplayStatics.h"


void USoundManager::Init(USoundMix* NewMusicMixModifier, USoundMix* NewSFXMixModifier, USoundClass* NewMusicClass, USoundClass* NewSFXClass)
{
	if (!NewMusicMixModifier || !NewSFXMixModifier || !NewMusicClass || !NewSFXClass) return;
	MusicMixModifier = NewMusicMixModifier;
	MusicClass = NewMusicClass;
	SFXMixModifier = NewSFXMixModifier;
	SFXClass = NewSFXClass;
}


void USoundManager::SetMusicVolume(const float Volume)
{
	MusicVolume = Volume;
	UGameplayStatics::SetSoundMixClassOverride(GetWorld(), MusicMixModifier, MusicClass, Volume, 1, 0, true);
	UGameplayStatics::PushSoundMixModifier(GetWorld(), MusicMixModifier);
}


void USoundManager::SetSFXVolume(const float Volume)
{
	SFXVolume = Volume;
	UGameplayStatics::SetSoundMixClassOverride(GetWorld(), SFXMixModifier, SFXClass, Volume, 1, 0, true);
	UGameplayStatics::PushSoundMixModifier(GetWorld(), SFXMixModifier);
}


float USoundManager::GetMusicVolume() const
{
	return MusicVolume;
}


float USoundManager::GetSFXVolume() const
{
	return SFXVolume;
}


