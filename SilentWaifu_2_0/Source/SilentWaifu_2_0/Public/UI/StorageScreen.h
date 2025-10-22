
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StorageScreen.generated.h"


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

	void CreateStorageCards();

	UPROPERTY(EditAnywhere)
	UWidgetReferenceDataAsset* WidgetReferences;
	
	UPROPERTY()
	ASilentWaifuGameMode* GameMode;


};
