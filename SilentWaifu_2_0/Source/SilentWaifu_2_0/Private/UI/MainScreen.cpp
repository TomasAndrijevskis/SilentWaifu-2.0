
#include "UI/MainScreen.h"

#include "Components/BackgroundBlur.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "GameMode/SilentWaifuGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "UI/WidgetReferenceDataAsset.h"
#include "UI/StorageScreen.h"


void UMainScreen::NativeConstruct()
{
	Super::NativeConstruct();
	GameMode = Cast<ASilentWaifuGameMode>(UGameplayStatics::GetGameMode(this));
	if (!GameMode)
	{
		return;
	}
	GameMode->OnMoneyChangedDelegate.AddDynamic(this, &UMainScreen::UpdateMoney);
	Button_Storage->OnClicked.AddDynamic(this, &UMainScreen::CreateStorage);
	FOnWindowStateChangedDelegate.AddDynamic(this, &UMainScreen::HandleBlur);
}


void UMainScreen::UpdateMoney(int const Money)
{
	Text_CurrentMoney->SetText(FText::FromString(FString::FromInt(Money)));
}


void UMainScreen::CreateStorage()
{
	if (WidgetReferences->StorageScreenClass)
	{
		WidgetReferences->StorageScreenRef = Cast<UStorageScreen>(CreateWidget(GetWorld(), WidgetReferences->StorageScreenClass));
		WidgetReferences->StorageScreenRef->AddToViewport(1);
		WidgetReferences->StorageScreenRef->Button_CloseStorage->OnClicked.AddDynamic(this, &UMainScreen::RemoveStorage);
		FOnWindowStateChangedDelegate.Broadcast(20.f);
	}
}


void UMainScreen::RemoveStorage()
{
	if (WidgetReferences->StorageScreenRef)
	{
		WidgetReferences->StorageScreenRef->RemoveFromParent();
		WidgetReferences->StorageScreenRef = nullptr;
		FOnWindowStateChangedDelegate.Broadcast(0.f);
	}
}


void UMainScreen::HandleBlur(const float BlurStrength)
{
	BackgroundBlur->SetBlurStrength(BlurStrength);
}
