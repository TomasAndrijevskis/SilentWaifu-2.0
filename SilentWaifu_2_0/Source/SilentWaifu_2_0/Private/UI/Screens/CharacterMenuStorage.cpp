
#include "UI/Screens/CharacterMenuStorage.h"
#include "Components/WrapBox.h"
#include "GameMode/SilentWaifuGameMode.h"
#include "GameMode/Helpers/CharactersManager.h"
#include "UI/WidgetReferenceDataAsset.h"
#include "UI/Cards/CharacterCardStorage.h"


void UCharacterMenuStorage::CreateCharacterMenu()
{
	if (!GameMode) return;

	for (const auto Character : GameMode->CharactersManager->GetSortedCharacters())
	{
		//UE_LOG(LogTemp, Warning, TEXT("Character %i created"), Character.Key);
		if (WidgetReferences->StorageCharacterCardClass)
		{
			WidgetReferences->StorageCharacterCardRef = Cast<UCharacterCardStorage>(CreateWidget(GetWorld(), WidgetReferences->StorageCharacterCardClass));
			WrapBox->AddChild(WidgetReferences->StorageCharacterCardRef);
			WidgetReferences->StorageCharacterCardRef->CreateCard(Character.Value.CharacterId);
		}
	}
}
