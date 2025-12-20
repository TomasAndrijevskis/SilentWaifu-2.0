
#include "UI/Cards/CharacterCard.h"
#include "DataTables/CharacterData.h"
#include "GameMode/SilentWaifuGameMode.h"


void UCharacterCard::CreateCard(const int NewCharacterId)
{
	CharacterId = NewCharacterId;
	Init();
	SetCharacterManager();
	SetCharacterData();
	if (!CharacterRow) return;
	SetImage(CharacterRow->Images.CardImage);
	OnCardCreatedDelegate.Broadcast();
}


void UCharacterCard::Init()
{
	Super::Init();
	SetCharacterManager();
}


void UCharacterCard::SetCharacterData()
{
	if (!CharacterDataTable) return;
	const FName RowName = FName(*FString::FromInt(CharacterId));
	CharacterRow = CharacterDataTable->FindRow<FCharacterData>(RowName, TEXT("Find Character By Id"));
}


void UCharacterCard::SetCharacterManager()
{
	if (!GameMode) return;
	CharactersManager = GameMode->CharactersManager;
}


FCharacterData* UCharacterCard::GetCharacterData()
{
	return CharacterRow;
}