
#include "UI/Screens/CharacterMenuChooseCharacter.h"
#include "Components/Button.h"
#include "Components/WrapBox.h"
#include "GameMode/Helpers/CharactersManager.h"
#include "UI/Screens/MainScreen.h"
#include "UI/WidgetReferenceDataAsset.h"
#include "UI/Cards/CharacterCardChoose.h"


void UCharacterMenuChooseCharacter::CreateCharacterMenu()
{
	if (!CharactersManager) return;
	for (const auto& Character : CharactersManager->GetSortedCharacters())
	{
		if (!WidgetReferences || !WidgetReferences->ChooseCharacterCardClass) return;
		WidgetReferences->ChooseCharacterCardRef = Cast<UCharacterCardChoose>(CreateWidget(GetWorld(), WidgetReferences->ChooseCharacterCardClass));
		if (!WidgetReferences->ChooseCharacterCardRef) return;
		WrapBox->AddChild(WidgetReferences->ChooseCharacterCardRef);
		WidgetReferences->ChooseCharacterCardRef->CreateCard(Character.Value.CharacterId);
		WidgetReferences->ChooseCharacterCardRef->Button_Action->OnClicked.AddDynamic(this,&UCharacterMenuBase::RemoveCharacterMenu);
	}
}


void UCharacterMenuChooseCharacter::RemoveCharacterMenu()
{
	if (!WidgetReferences->ChooseScreenRef) return;
	WidgetReferences->ChooseScreenRef->RemoveFromParent();
	WidgetReferences->ChooseScreenRef = nullptr;
	WidgetReferences->MainScreenRef->OnWindowStateChangedDelegate.Broadcast(true);
}
