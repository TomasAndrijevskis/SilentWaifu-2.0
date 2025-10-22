
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StorageScreen.generated.h"


class UTextBlock;
class UHorizontalBox;
class UWidgetReferenceDataAsset;
class ASilentWaifuGameMode;
class UButton;
class UWrapBox;
class UScrollBox;

UCLASS()
class SILENTWAIFU_2_0_API UStorageScreen : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UPROPERTY(meta = (BindWidget))
	UButton* Button_CloseStorage;
	
	virtual void NativeConstruct() override;
	
private:

	UPROPERTY(meta = (BindWidget))
	UScrollBox* ScrollBox;
	
	UPROPERTY(meta = (BindWidget))
	UWrapBox* WrapBox;

	UPROPERTY(meta=(BindWidget))
	UHorizontalBox* HorizontalBox_Header;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Text_Exit;
	
	void CreateStorageCards();

	UPROPERTY(EditAnywhere)
	UWidgetReferenceDataAsset* WidgetReferences;
	
	UPROPERTY()
	ASilentWaifuGameMode* GameMode;


};
