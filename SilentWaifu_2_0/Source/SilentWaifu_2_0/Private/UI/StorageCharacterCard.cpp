
#include "UI/StorageCharacterCard.h"


void UStorageCharacterCard::NativeConstruct()
{
	Super::NativeConstruct();
	CreateCard();
}

void UStorageCharacterCard::CreateCard()
{
	UE_LOG(LogTemp, Warning, TEXT("UStorageCharacterCard::CreateCard"));
}
