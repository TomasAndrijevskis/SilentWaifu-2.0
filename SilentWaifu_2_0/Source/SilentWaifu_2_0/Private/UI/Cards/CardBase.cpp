
#include "UI/Cards/CardBase.h"
#include "Components/Button.h"
#include "DataTables/CharacterData.h"
#include "GameMode/SilentWaifuGameMode.h"
#include "Kismet/GameplayStatics.h"


void UCardBase::NativeConstruct()
{
	Super::NativeConstruct();
	GameMode = Cast<ASilentWaifuGameMode>(UGameplayStatics::GetGameMode(this));
	if (!GameMode) return;
	Button_Action->OnClicked.AddDynamic(this, &UCardBase::Action);
}


void UCardBase::CreateCard(const int Id)
{
	if (!CharacterDataTable) return;
	const FName RowName = FName(*FString::FromInt(Id));
	const FCharacterData* CharacterRow = CharacterDataTable->FindRow<FCharacterData>(RowName, TEXT("Find Character By Id"));
	if (!CharacterRow)	return;
	CharacterId = CharacterRow->CharacterId;
	SetImage(CharacterRow->CardImage);
}
