
#pragma once

#include "CoreMinimal.h"
#include "SoundManager.generated.h"


UCLASS()
class SILENTWAIFU_2_0_API USoundManager : public UObject
{
	GENERATED_BODY()

public:

	void Init(USoundMix* NewMusicMixModifier, USoundMix* NewSFXMixModifier, USoundClass* NewMusicClass, USoundClass* NewSFXClass);

	UFUNCTION()
	void SetMusicVolume(const float Volume);

	UFUNCTION()
	void SetSFXVolume(const float Volume);

	float GetMusicVolume() const;

	float GetSFXVolume() const;
	 
private:
	
	UPROPERTY()
	USoundMix* MusicMixModifier;

	UPROPERTY()
	USoundMix* SFXMixModifier;

	UPROPERTY()
	USoundClass* MusicClass;

	UPROPERTY()
	USoundClass* SFXClass;
	
	float MusicVolume;

	float SFXVolume;
};
