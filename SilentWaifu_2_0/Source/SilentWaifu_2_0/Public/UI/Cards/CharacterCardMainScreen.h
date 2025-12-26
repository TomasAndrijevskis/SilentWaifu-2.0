
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

	virtual void ApplyCardBrushStyle(FSlateBrush& BrushStyle, UTexture2D* Image) override;
	
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

	void SetAbilityImage();

	void ApplyAbilityBrushStyle(FSlateBrush& BrushStyle, UTexture2D* AbilityImage) const;
	
	UTexture2D* GetAbilityImage();
	
	UPROPERTY(EditAnywhere)
	UDataTable* RarityDataTable;
	
	FTimerHandle TimerHandle;
};
