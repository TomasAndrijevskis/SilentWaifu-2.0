
#include "UI/Screens/CharacterMenuStorage.h"
#include "Components/WrapBox.h"
#include "GameMode/SilentWaifuGameMode.h"
#include "GameMode/Helpers/CharactersManager.h"
#include "UI/WidgetReferenceDataAsset.h"
#include "UI/Cards/CharacterCardStorage.h"


void UCharacterMenuStorage::CreateCharacterMenu()
{
	if (!GameMode) return;
	for (const auto& Character : GameMode->CharactersManager->GetSortedCharacters())
	{
		if (!WidgetReferences || !WidgetReferences->StorageCharacterCardClass) return;
		WidgetReferences->StorageCharacterCardRef = Cast<UCharacterCardStorage>(CreateWidget(GetWorld(), WidgetReferences->StorageCharacterCardClass));
		if (!WidgetReferences->StorageCharacterCardRef) return;
		WrapBox->AddChild(WidgetReferences->StorageCharacterCardRef);
		WidgetReferences->StorageCharacterCardRef->CreateCard(Character.Value.CharacterId);
	}
}
