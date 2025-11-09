
#pragma once

#include "CoreMinimal.h"
#include "UI/Cards/CardBase.h"
#include "CharacterCard.generated.h"


class UCharactersManager;

UCLASS()
class SILENTWAIFU_2_0_API UCharacterCard : public UCardBase
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;
	
	virtual void CreateCard(const int NewCharacterId) override;

protected:

	UPROPERTY(EditAnywhere)
	UDataTable* CharacterDataTable;
	
	int CharacterId;

	UPROPERTY()
	UCharactersManager* CharactersManager;

private:

	void SetCharacterManager();

};
