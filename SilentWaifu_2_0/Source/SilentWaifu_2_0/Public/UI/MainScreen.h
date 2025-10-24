
#pragma once

#include "CoreMinimal.h"
#include "WidgetReferenceDataAsset.h"
#include "Blueprint/UserWidget.h"
#include "MainScreen.generated.h"

class UVerticalBox;
class UBackgroundBlur;
class ASilentWaifuGameMode;
class UButton;
class UTextBlock;
class UHorizontalBox;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWindowStateChangedSignature, bool, State);

UCLASS()
class SILENTWAIFU_2_0_API UMainScreen : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;

	UFUNCTION()
	void UpdateMoney(int const Money);

	FOnWindowStateChangedSignature FOnWindowStateChangedDelegate;
	
protected:
	
	UPROPERTY(EditAnywhere)
	UWidgetReferenceDataAsset* WidgetReferences;

private:

	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* HorizontalBox_MoneyPanel;

	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* HorizontalBox_CharacterSlots;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* VerticalBox_Characters;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_CurrentMoney;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Storage;

	UPROPERTY(meta = (BindWidget))
	UBackgroundBlur* BackgroundBlur;
	
	UFUNCTION()
	void CreateStorage();

	UFUNCTION()
	void RemoveStorage();
	
	void HandleBlur(const float BlurStrength);

	UFUNCTION()
	void HandleWindowState(const bool NewState);

	void CreateSlots();

	void CreateButtons();
	
	UPROPERTY()
	ASilentWaifuGameMode* GameMode;

	int AmountOfSlots = 5;
};

