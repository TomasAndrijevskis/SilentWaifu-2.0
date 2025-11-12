
#include "UI/Cards/CharacterCard.h"
#include "DataTables/CharacterData.h"
#include "GameMode/SilentWaifuGameMode.h"


void UCharacterCard::CreateCard(const int NewCharacterId)
{
	Init();
	if (!CharacterDataTable) return;
	const FName RowName = FName(*FString::FromInt(NewCharacterId));
	const FCharacterData* CharacterRow = CharacterDataTable->FindRow<FCharacterData>(RowName, TEXT("Find Character By Id"));
	if (!CharacterRow)	return;
	CharacterId = CharacterRow->CharacterId;
	SetImage(CharacterRow->Images.CardImage);
	OnCardCreatedDelegate.Broadcast();
}


void UCharacterCard::Init()
{
	Super::Init();
	SetCharacterManager();
}


void UCharacterCard::SetCharacterManager()
{
	if (!GameMode) return;
	CharactersManager = GameMode->CharactersManager;
}
