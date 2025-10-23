
#include "UI/CharacterCardBase.h"
#include "Components/Button.h"
#include "DataTables/CharacterData.h"


void UCharacterCardBase::NativeConstruct()
{
	Super::NativeConstruct();
	Button_Character->OnClicked.AddDynamic(this, &UCharacterCardBase::Action);
}


void UCharacterCardBase::CreateCard(const int Id)
{
	UE_LOG(LogTemp, Warning, TEXT("UCharacterCardBase::CreateCard"));
	if (!CharacterDataTable) return;
	const FName RowName = FName(*FString::FromInt(Id));
	const FCharacterData* CharacterRow = CharacterDataTable->FindRow<FCharacterData>(RowName, TEXT("Find Character By Id"));
	if (!CharacterRow)	return;
	SetImage(CharacterRow->Image);
	CharacterId = Id;
}
