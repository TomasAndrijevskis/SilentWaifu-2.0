
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterMenuBase.generated.h"

class UVerticalBox;
class USizeBox;
class UBorder;
class UTextBlock;
class UHorizontalBox;
class UWidgetReferenceDataAsset;
class ASilentWaifuGameMode;
class UButton;
class UWrapBox;
class UScrollBox;

UCLASS()
class SILENTWAIFU_2_0_API UCharacterMenuBase : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(meta = (BindWidget))
	UButton* Button_Close;
	
	virtual void NativeConstruct() override;

	UFUNCTION()
	virtual void RemoveCharacterMenu(){};
	
protected:
	
	UPROPERTY(meta = (BindWidget))
	UWrapBox* WrapBox;

	virtual void CreateCharacterMenu(){};
	
	UPROPERTY(EditAnywhere)
	UWidgetReferenceDataAsset* WidgetReferences;
	
	UPROPERTY()
	ASilentWaifuGameMode* GameMode;
	
private:

	UPROPERTY(meta = (BindWidget))
	UScrollBox* ScrollBox;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* VerticalBox_Content;
	
	UPROPERTY(meta = (BindWidget))
	USizeBox* SizeBox;

	UPROPERTY(meta=(BindWidget))
	UBorder* Border_ScreenBorder;

	UPROPERTY(meta=(BindWidget))
	UBorder* Border;
};
