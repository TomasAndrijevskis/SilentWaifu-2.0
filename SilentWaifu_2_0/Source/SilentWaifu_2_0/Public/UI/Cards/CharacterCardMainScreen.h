
#pragma once

#include "CoreMinimal.h"
#include "CharacterCard.h"
#include "CharacterCardMainScreen.generated.h"


class UWidgetReferenceDataAsset;
class UButton;

UCLASS()
class SILENTWAIFU_2_0_API UCharacterCardMainScreen : public UCharacterCard
{
	GENERATED_BODY()

public:

	virtual void Init() override;
	
protected:

	virtual void SetImage(UTexture2D* NewImage) override;
	
	virtual void Action() override;

private:

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Ability;

	UFUNCTION()
	void OnCardCreated();
	
	UFUNCTION()
	void ActivateAbility();
	
	UFUNCTION()
	void EnablePressedTimer();

	UFUNCTION()
	void DisablePressedTimer();
	
	FTimerHandle TimerHandle;
};
