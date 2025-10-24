
#include "UI/MainScreen.h"
#include "Components/BackgroundBlur.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "GameMode/SilentWaifuGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "UI/CharacterMenuChooseCharacter.h"
#include "UI/CharacterMenuStorage.h"


void UMainScreen::NativeConstruct()
{
	Super::NativeConstruct();
	GameMode = Cast<ASilentWaifuGameMode>(UGameplayStatics::GetGameMode(this));
	if (!GameMode) return;
	GameMode->OnMoneyChangedDelegate.AddDynamic(this, &UMainScreen::UpdateMoney);
	Button_Storage->OnClicked.AddDynamic(this, &UMainScreen::CreateStorage);
	FOnWindowStateChangedDelegate.AddDynamic(this, &UMainScreen::HandleWindowState);
}


void UMainScreen::UpdateMoney(int const Money)
{
	Text_CurrentMoney->SetText(FText::FromString(FString::FromInt(Money)));
}


void UMainScreen::CreateStorage()
{
	if (WidgetReferences->StorageScreenClass)
	{
		WidgetReferences->StorageScreenRef = Cast<UCharacterMenuStorage>(CreateWidget(GetWorld(), WidgetReferences->StorageScreenClass));
		WidgetReferences->StorageScreenRef->AddToViewport(1);
		WidgetReferences->StorageScreenRef->Button_Close->OnClicked.AddDynamic(this, &UMainScreen::RemoveStorage);
		FOnWindowStateChangedDelegate.Broadcast(false);
	}
}


void UMainScreen::RemoveStorage()
{
	if (WidgetReferences->StorageScreenRef)
	{
		WidgetReferences->StorageScreenRef->RemoveFromParent();
		WidgetReferences->StorageScreenRef = nullptr;
		FOnWindowStateChangedDelegate.Broadcast(true);
	}
}


void UMainScreen::HandleWindowState(const bool NewState)
{
	Button_Storage->SetIsEnabled(NewState);
	if (!NewState)
	{
		HandleBlur(20.f);
	}
	else
	{
		HandleBlur(0.f);
	}
}


void UMainScreen::HandleBlur(const float BlurStrength)
{
	BackgroundBlur->SetBlurStrength(BlurStrength);
}
