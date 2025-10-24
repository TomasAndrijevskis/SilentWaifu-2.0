
#include "UI/CreateChooseScreenButton.h"
#include "Components/Button.h"
#include "GameMode/SilentWaifuGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "UI/CharacterMenuChooseCharacter.h"
#include "UI/MainScreen.h"
#include "UI/WidgetReferenceDataAsset.h"


void UCreateChooseScreenButton::NativeConstruct()
{
	Super::NativeConstruct();
	GameMode = Cast<ASilentWaifuGameMode>(UGameplayStatics::GetGameMode(this));
	if (!GameMode) return;
	Button_CreateChooseScreen->OnClicked.AddDynamic(this, &UCreateChooseScreenButton::CreateChooseScreen);
}


void UCreateChooseScreenButton::CreateChooseScreen()
{
	if (WidgetReferences->ChooseScreenClass)
	{
		WidgetReferences->ChooseScreenRef = Cast<UCharacterMenuChooseCharacter>(CreateWidget(GetWorld(), WidgetReferences->ChooseScreenClass));
		WidgetReferences->ChooseScreenRef->AddToViewport(1);
		WidgetReferences->ChooseScreenRef->Button_Close->OnClicked.AddDynamic(this, &UCreateChooseScreenButton::RemoveChooseScreen);
		WidgetReferences->MainScreenRef->FOnWindowStateChangedDelegate.Broadcast(false);
	}
}


void UCreateChooseScreenButton::RemoveChooseScreen()
{
	if (WidgetReferences->ChooseScreenRef)
	{
		WidgetReferences->ChooseScreenRef->RemoveFromParent();
		WidgetReferences->ChooseScreenRef = nullptr;
		WidgetReferences->MainScreenRef->FOnWindowStateChangedDelegate.Broadcast(true);
	}
}
