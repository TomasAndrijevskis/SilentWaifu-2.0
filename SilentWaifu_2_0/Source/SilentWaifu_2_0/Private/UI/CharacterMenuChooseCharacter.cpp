
#include "UI/CharacterMenuChooseCharacter.h"
#include "Components/WrapBox.h"
#include "GameMode/SilentWaifuGameMode.h"
#include "UI/CharacterCardBase.h"
#include "UI/CharacterCardChoose.h"
#include "UI/WidgetReferenceDataAsset.h"


void UCharacterMenuChooseCharacter::CreateCharacterMenu()
{
	if (!GameMode)return;
	for (const auto Character : GameMode->GetAvailableCharacters())
	{
		UE_LOG(LogTemp, Warning, TEXT("Character %i created"), Character.Key);
		if (WidgetReferences->ChooseCharacterCardClass)
		{
			WidgetReferences->ChooseCharacterCardRef = Cast<UCharacterCardChoose>(CreateWidget(GetWorld(), WidgetReferences->ChooseCharacterCardClass));
			WrapBox->AddChild(WidgetReferences->ChooseCharacterCardRef);
			WidgetReferences->ChooseCharacterCardRef->CreateCard(Character.Value.CharacterId);
		}
	}
}
