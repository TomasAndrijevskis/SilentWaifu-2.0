
#include "UI/ButtonCreateChooseScreen.h"
#include "Components/Button.h"
#include "GameMode/SilentWaifuGameMode.h"
#include "GameMode/Helpers/CharactersManager.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Screens/CharacterMenuChooseCharacter.h"
#include "UI/Screens/MainScreen.h"
#include "UI/WidgetReferenceDataAsset.h"


void UButtonCreateChooseScreen::NativeConstruct()
{
	Super::NativeConstruct();
	GameMode = Cast<ASilentWaifuGameMode>(UGameplayStatics::GetGameMode(this));
	if (!GameMode) return;
	Button_CreateChooseScreen->OnClicked.AddDynamic(this, &UButtonCreateChooseScreen::CreateChooseScreen);
}


void UButtonCreateChooseScreen::CreateChooseScreen()
{
	if (!WidgetReferences || !WidgetReferences->ChooseScreenClass) return;
	WidgetReferences->ChooseScreenRef = Cast<UCharacterMenuChooseCharacter>(CreateWidget(GetWorld(), WidgetReferences->ChooseScreenClass));
	if (!WidgetReferences->ChooseScreenRef) return;
	WidgetReferences->ChooseScreenRef->AddToViewport(1);
	GameMode->CharactersManager->SetCurrentSpawnPosition(GetSpawnPosition());
}



void UButtonCreateChooseScreen::SetSpawnPosition(const int NewSpawnPosition)
{
	SpawnPosition = NewSpawnPosition;
}


int UButtonCreateChooseScreen::GetSpawnPosition() const
{
	return SpawnPosition;
}

