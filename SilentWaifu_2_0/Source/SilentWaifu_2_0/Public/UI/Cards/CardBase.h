
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CardBase.generated.h"


class ACharacterTemplate;
class ASilentWaifuGameMode;
class UBorder;
class UButton;

UCLASS()
class SILENTWAIFU_2_0_API UCardBase : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Action;
	
	virtual void NativeConstruct() override;
	
	virtual void CreateCard(const int Id);

protected:
	
	virtual void SetImage(UTexture2D* NewImage){};

	UFUNCTION()
	virtual void Action(){};
	
	UPROPERTY(EditDefaultsOnly)
	FVector2D ImageSize = FVector2D(340, 540);

	UPROPERTY(EditAnywhere)
	ASilentWaifuGameMode* GameMode;

	UPROPERTY(EditAnywhere)
	UDataTable* CharacterDataTable;
	
	int CharacterId;

private:

	UPROPERTY(meta = (BindWidget))
	UBorder* Border_Padding;
	
};
