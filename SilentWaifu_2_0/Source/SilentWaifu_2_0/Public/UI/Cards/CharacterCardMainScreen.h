
#pragma once

#include "CoreMinimal.h"
#include "CharacterCard.h"
#include "DataTables/CharacterRarities.h"
#include "SaveGame/SavedCharactersData.h"
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

	UFUNCTION()
	void HandleAbilityButtonState();
	
	void SetAbilityImage();

	void ApplyAbilityBrushStyle(FSlateBrush& BrushStyle, UTexture2D* AbilityImage) const;

	FSavedCharactersData* GetCharactersSavedData() const;

	FCharacterRarities* GetCharacterRarity();
	
	bool CanUseAbility();
	
	UTexture2D* GetAbilityImage();
	
	void SetCooldownTimer();

	UFUNCTION()
	void OnCooldownFinished();
	
	UPROPERTY(EditAnywhere)
	UDataTable* RarityDataTable;
	
	FTimerHandle PressedTimerHandle;

	FTimerHandle CooldownTimerHandle;
};
