
#pragma once

#include "CoreMinimal.h"
#include "DataTables/CharacterData.h"
#include "UI/Cards/CardBase.h"
#include "CharacterCard.generated.h"


class UCharactersManager;

UCLASS()
class SILENTWAIFU_2_0_API UCharacterCard : public UCardBase
{
	GENERATED_BODY()

public:
	
	virtual void CreateCard(const int NewCharacterId) override;

	virtual void Init() override;

	FCharacterData* GetCharacterData();
	
protected:

	void SetCharacterData();
	
	UPROPERTY(EditAnywhere)
	UDataTable* CharacterDataTable;
	
	UPROPERTY()
	UCharactersManager* CharactersManager;
	
	int CharacterId;

private:

	void SetCharacterManager();

	FCharacterData* CharacterRow;
};
