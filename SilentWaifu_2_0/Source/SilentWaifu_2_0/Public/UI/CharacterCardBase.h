
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterCardBase.generated.h"


class UBorder;
class UButton;

UCLASS()
class SILENTWAIFU_2_0_API UCharacterCardBase : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;
	
	void CreateCard(const int Id);

protected:

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Character;
	
	virtual void SetImage(UTexture2D* NewImage){};

	UFUNCTION()
	virtual void Action(){};
	
	UPROPERTY(EditDefaultsOnly)
	FVector2D ImageSize = FVector2D(280, 420);

	int CharacterId;
private:

	UPROPERTY(meta = (BindWidget))
	UBorder* Border_Padding;

	UPROPERTY(EditAnywhere)
	UDataTable* CharacterDataTable;
	
};
