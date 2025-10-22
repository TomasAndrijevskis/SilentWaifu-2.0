
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StorageCharacterCard.generated.h"


class UButton;

UCLASS()
class SILENTWAIFU_2_0_API UStorageCharacterCard : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;
	
	void CreateCard();
	
private:

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Character;
	
};
