
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
	//UE_LOG(LogTemp, Error, TEXT("Creating ChooseScreen: %i"), GetSpawnPosition());
	if (WidgetReferences->ChooseScreenClass)
	{
		WidgetReferences->ChooseScreenRef = Cast<UCharacterMenuChooseCharacter>(CreateWidget(GetWorld(), WidgetReferences->ChooseScreenClass));
		WidgetReferences->ChooseScreenRef->AddToViewport(1);
		WidgetReferences->MainScreenRef->OnWindowStateChangedDelegate.Broadcast(false);
		GameMode->CharactersManager->SetCurrentSpawnPosition(GetSpawnPosition());
	}
}



void UButtonCreateChooseScreen::SetSpawnPosition(const int NewSpawnPosition)
{
	SpawnPosition = NewSpawnPosition;
}


int UButtonCreateChooseScreen::GetSpawnPosition() const
{
	return SpawnPosition;
}

