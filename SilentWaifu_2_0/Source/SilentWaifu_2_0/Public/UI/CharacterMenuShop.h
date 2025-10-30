
#pragma once

#include "CoreMinimal.h"
#include "UI/CharacterMenuBase.h"
#include "CharacterMenuShop.generated.h"


UCLASS()
class SILENTWAIFU_2_0_API UCharacterMenuShop : public UCharacterMenuBase
{
	GENERATED_BODY()

protected:

	virtual void CreateCharacterMenu() override;

private:

	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* HorizontalBox_Shop;

	int GetCharactersCount() const;

	TArray<int> GetRandomCharacters() const;
	
	UPROPERTY(EditAnywhere)
	UDataTable* CharacterDataTable;
};
