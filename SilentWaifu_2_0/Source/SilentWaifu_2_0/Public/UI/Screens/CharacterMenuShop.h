
#pragma once

#include "CoreMinimal.h"
#include "UI/Screens/CharacterMenuBase.h"
#include "CharacterMenuShop.generated.h"


UCLASS()
class SILENTWAIFU_2_0_API UCharacterMenuShop : public UCharacterMenuBase
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	UFUNCTION()
	void UpdateShop();
	
protected:

	virtual void CreateCharacterMenu() override;

private:

	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* HorizontalBox_Shop;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_UpdateShop;//testing
	
	int GetCharactersCount() const;

	TArray<int> GetRandomCharacters() const;

	void CreateShop(TArray<int> Characters);
	
	UPROPERTY(EditAnywhere)
	UDataTable* CharacterDataTable;

	int AmountOfSlots = 5;
};
