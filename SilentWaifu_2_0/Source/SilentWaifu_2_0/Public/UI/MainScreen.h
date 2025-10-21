
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainScreen.generated.h"

class ASilentWaifuGameMode;
class UTextBlock;
class UHorizontalBox;


UCLASS()
class SILENTWAIFU_2_0_API UMainScreen : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;

	UFUNCTION()
	void UpdateMoney(int const Money);
	
private:

	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* HorizontalBox_MoneyPanel;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_CurrentMoney;
	
	UPROPERTY()
	ASilentWaifuGameMode* GameMode;
};
