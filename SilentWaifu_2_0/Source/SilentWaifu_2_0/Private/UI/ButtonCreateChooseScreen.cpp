
#include "UI/ButtonCreateChooseScreen.h"
#include "Components/Button.h"
#include "GameMode/SilentWaifuGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "UI/CharacterMenuChooseCharacter.h"
#include "UI/MainScreen.h"
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
	UE_LOG(LogTemp, Error, TEXT("Creating ChooseScreen"));
	if (WidgetReferences->ChooseScreenClass)
	{
		WidgetReferences->ChooseScreenRef = Cast<UCharacterMenuChooseCharacter>(CreateWidget(GetWorld(), WidgetReferences->ChooseScreenClass));
		WidgetReferences->ChooseScreenRef->AddToViewport(1);
		WidgetReferences->MainScreenRef->FOnWindowStateChangedDelegate.Broadcast(false);
	}
}
