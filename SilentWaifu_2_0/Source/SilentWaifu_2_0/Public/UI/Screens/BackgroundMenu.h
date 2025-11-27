
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DataTables/BackgroundData.h"
#include "BackgroundMenu.generated.h"


class UHorizontalBox;
class UBackgroundCard;
class UBackgroundBlur;
class UBorder;
class UScrollBox;
class ASilentWaifuGameMode;
class UWidgetReferenceDataAsset;
class UWrapBox;
class UButton;

UCLASS()
class SILENTWAIFU_2_0_API UBackgroundMenu : public UUserWidget
{
	GENERATED_BODY()


public:
	
	virtual void NativeConstruct() override;

protected:
	
	UPROPERTY(meta = (BindWidget))
	UWrapBox* WrapBox;
	
	UPROPERTY(EditAnywhere)
	UWidgetReferenceDataAsset* WidgetReferences;
	
	UPROPERTY()
	ASilentWaifuGameMode* GameMode;
	
private:

	UPROPERTY(meta = (BindWidget))
	UScrollBox* ScrollBox;

	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* HorizontalBox_Content;

	UPROPERTY(meta=(BindWidget))
	UBorder* Border_ScreenBorder;

	UPROPERTY(meta=(BindWidget))
	UBorder* Border;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_InputBlocker;

	UPROPERTY(meta=(BindWidget))
	UBackgroundBlur* Blur;
	
	UPROPERTY(meta = (BindWidget))
	UButton* Button_Close;
	
	UPROPERTY(EditAnywhere)
	UDataTable* BackgroundsDataTable;

	UFUNCTION()
	void RemoveMenu();
	
	void CreateCards();

	UBackgroundCard* CreateBackgroundCard(UTexture2D* Image, int Id, int Price) const;

	TArray<FBackgroundData*> GetBackgroundData() const;
};
