
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StorageScreen.generated.h"


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
	
private:

	UPROPERTY(meta = (BindWidget))
	UScrollBox* ScrollBox;
	
	UPROPERTY(meta = (BindWidget))
	UWrapBox* WrapBox;


};
