
#include "UI/CharacterMenuChooseCharacter.h"
#include "Components/Button.h"
#include "Components/WrapBox.h"
#include "GameMode/SilentWaifuGameMode.h"
#include "UI/MainScreen.h"
#include "UI/WidgetReferenceDataAsset.h"
#include "UI/Cards/CharacterCardChoose.h"


void UCharacterMenuChooseCharacter::CreateCharacterMenu()
{
	if (!GameMode) return;
	for (const auto Character : GameMode->GetSortedCharacters())
	{
		if (WidgetReferences->ChooseCharacterCardClass)
		{
			WidgetReferences->ChooseCharacterCardRef = Cast<UCharacterCardChoose>(CreateWidget(GetWorld(), WidgetReferences->ChooseCharacterCardClass));
			WrapBox->AddChild(WidgetReferences->ChooseCharacterCardRef);
			WidgetReferences->ChooseCharacterCardRef->CreateCard(Character.Value.CharacterId);
			WidgetReferences->ChooseCharacterCardRef->Button_Character->OnClicked.AddDynamic(this,&UCharacterMenuBase::RemoveCharacterMenu);
		}
	}
}


void UCharacterMenuChooseCharacter::RemoveCharacterMenu()
{
	if (WidgetReferences->ChooseScreenRef)
	{
		WidgetReferences->ChooseScreenRef->RemoveFromParent();
		WidgetReferences->ChooseScreenRef = nullptr;
		WidgetReferences->MainScreenRef->OnWindowStateChangedDelegate.Broadcast(true);
	}
}
