
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CreateChooseScreenButton.generated.h"

class UWidgetReferenceDataAsset;
class ASilentWaifuGameMode;
class UButton;

UCLASS()
class SILENTWAIFU_2_0_API UCreateChooseScreenButton : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UWidgetReferenceDataAsset* WidgetReferences;
	
private:

	UPROPERTY(meta = (BindWidget))
	UButton* Button_CreateChooseScreen;

	UFUNCTION()
	void CreateChooseScreen();

	UFUNCTION()
	void RemoveChooseScreen();
	
	UPROPERTY()
	ASilentWaifuGameMode* GameMode;
};
