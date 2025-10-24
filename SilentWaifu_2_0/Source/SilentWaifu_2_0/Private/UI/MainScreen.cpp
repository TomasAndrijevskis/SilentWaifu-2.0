
#include "UI/MainScreen.h"
#include "Components/BackgroundBlur.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "GameMode/SilentWaifuGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "UI/CharacterMenuStorage.h"
#include "UI/ButtonCreateChooseScreen.h"


void UMainScreen::NativeConstruct()
{
	Super::NativeConstruct();
	GameMode = Cast<ASilentWaifuGameMode>(UGameplayStatics::GetGameMode(this));
	if (!GameMode) return;
	GameMode->OnMoneyChangedDelegate.AddDynamic(this, &UMainScreen::UpdateMoney);
	Button_Storage->OnClicked.AddDynamic(this, &UMainScreen::CreateStorage);
	FOnWindowStateChangedDelegate.AddDynamic(this, &UMainScreen::HandleWindowState);
	CreateSlots();
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


void UMainScreen::CreateSlots()
{
	for (int i = 0 ; i < AmountOfSlots; i++)
	{
		UVerticalBox* VB = NewObject<UVerticalBox>(this);
		UHorizontalBoxSlot* HBSlot = Cast<UHorizontalBoxSlot>(HorizontalBox_CharacterSlots->AddChild(VB));
		if (HBSlot)
		{
			HBSlot->SetSize( FSlateChildSize(ESlateSizeRule::Fill));
		}
	}
	CreateButtons();
}


void UMainScreen::CreateButtons()
{
	for (const auto CharacterSlot : HorizontalBox_CharacterSlots->GetAllChildren())
	{
		UButtonCreateChooseScreen* Button = CreateWidget<UButtonCreateChooseScreen>(GetWorld(), WidgetReferences->ButtonCreateChooseScreenClass);
		Cast<UVerticalBox>(CharacterSlot)->AddChild(Button);
	}
}


void UMainScreen::HandleBlur(const float BlurStrength)
{
	BackgroundBlur->SetBlurStrength(BlurStrength);
}
