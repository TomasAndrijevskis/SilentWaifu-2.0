
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ButtonCreateChooseScreen.generated.h"

class UWidgetReferenceDataAsset;
class ASilentWaifuGameMode;
class UButton;

UCLASS()
class SILENTWAIFU_2_0_API UButtonCreateChooseScreen : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

protected:

	UPROPERTY(EditAnywhere)
	UWidgetReferenceDataAsset* WidgetReferences;
	
private:

	UPROPERTY(meta = (BindWidget))
	UButton* Button_CreateChooseScreen;

	UFUNCTION()
	void CreateChooseScreen();
	
	UPROPERTY()
	ASilentWaifuGameMode* GameMode;
};
