
#include "UI/Cards/CharacterCard.h"
#include "DataTables/CharacterData.h"


void UCharacterCard::CreateCard(const int NewCharacterId)
{
	if (!CharacterDataTable) return;
	const FName RowName = FName(*FString::FromInt(NewCharacterId));
	const FCharacterData* CharacterRow = CharacterDataTable->FindRow<FCharacterData>(RowName, TEXT("Find Character By Id"));
	if (!CharacterRow)	return;
	CharacterId = CharacterRow->CharacterId;
	SetImage(CharacterRow->CardImage);
	OnCardCreatedDelegate.Broadcast();
}
