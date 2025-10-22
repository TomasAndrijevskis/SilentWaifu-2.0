
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StorageCharacterCard.generated.h"


class UBorder;
class UButton;

UCLASS()
class SILENTWAIFU_2_0_API UStorageCharacterCard : public UUserWidget
{
	GENERATED_BODY()
	
public:

	void CreateCard(const int Id);
	
private:

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Character;

	UPROPERTY(meta = (BindWidget))
	UBorder* Border_Padding;
	
	UPROPERTY(EditAnywhere)
	UDataTable* CharacterDataTable;

	void SetImage(UTexture2D* NewImage);

	UPROPERTY(EditDefaultsOnly)
	FVector2D ImageSize = FVector2D(280, 420);
};
