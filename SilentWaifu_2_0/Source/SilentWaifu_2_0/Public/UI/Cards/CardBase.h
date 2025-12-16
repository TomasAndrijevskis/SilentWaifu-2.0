
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CardBase.generated.h"


class UMoneyManager;
class ACharacterTemplate;
class ASilentWaifuGameMode;
class UBorder;
class UButton;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCardCreatedSignature);
UCLASS()
class SILENTWAIFU_2_0_API UCardBase : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Action;
	
	virtual void Init();
	
	virtual void CreateCard(const int NewCharacterId) {};

	virtual void CreateCard() {}

	FOnCardCreatedSignature OnCardCreatedDelegate;
	
protected:
	
	virtual void SetImage(UTexture2D* NewImage){};

	UFUNCTION()
	virtual void Action(){};
	
	UPROPERTY(EditDefaultsOnly)
	FVector2D ImageSize = FVector2D(340, 540);

	UPROPERTY()
	ASilentWaifuGameMode* GameMode;

	UPROPERTY()
	UMoneyManager* MoneyManager;
	
private:

	UPROPERTY(meta = (BindWidget))
	UBorder* Border_Padding;
	
};
