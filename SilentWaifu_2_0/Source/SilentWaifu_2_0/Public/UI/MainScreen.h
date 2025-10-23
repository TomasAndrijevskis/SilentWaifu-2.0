
#pragma once

#include "CoreMinimal.h"
#include "WidgetReferenceDataAsset.h"
#include "Blueprint/UserWidget.h"
#include "MainScreen.generated.h"

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
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UWidgetReferenceDataAsset* WidgetReferences;

private:

	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* HorizontalBox_MoneyPanel;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_CurrentMoney;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Storage;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_ChooseScreen;

	UPROPERTY(meta = (BindWidget))
	UBackgroundBlur* BackgroundBlur;
	
	UFUNCTION()
	void CreateStorage();

	UFUNCTION()
	void RemoveStorage();

	UFUNCTION()
	void CreateChooseScreen();

	UFUNCTION()
	void RemoveChooseScreen();
	
	void HandleBlur(const float BlurStrength);

	UFUNCTION()
	void HandleWindowState(const bool NewState);
	
	UPROPERTY()
	ASilentWaifuGameMode* GameMode;

};

