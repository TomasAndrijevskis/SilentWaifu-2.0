
#include "UI/Screens/CharacterMenuStorage.h"
#include "Components/WrapBox.h"
#include "GameMode/SilentWaifuGameMode.h"
#include "GameMode/Helpers/CharactersManager.h"
#include "UI/WidgetReferenceDataAsset.h"
#include "UI/Cards/CharacterCardStorage.h"


void UCharacterMenuStorage::CreateCharacterMenu()
{
	if (!CharactersManager) return;
	for (const auto& Character : CharactersManager->GetSortedCharacters())
	{
		if (!WidgetReferences || !WidgetReferences->StorageCharacterCardClass) return;
		WidgetReferences->StorageCharacterCardRef = Cast<UCharacterCardStorage>(CreateWidget(GetWorld(), WidgetReferences->StorageCharacterCardClass));
		if (!WidgetReferences->StorageCharacterCardRef) return;
		WrapBox->AddChild(WidgetReferences->StorageCharacterCardRef);
		WidgetReferences->StorageCharacterCardRef->CreateCard(Character.Value.CharacterId);
	}
}
