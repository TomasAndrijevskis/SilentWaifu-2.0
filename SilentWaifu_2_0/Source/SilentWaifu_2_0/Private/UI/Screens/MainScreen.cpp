
#include "UI/Screens/MainScreen.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/Image.h"
#include "Components/VerticalBox.h"
#include "GameMode/SilentWaifuGameMode.h"
#include "GameMode/Helpers/BackgroundManager.h"
#include "GameMode/Helpers/CharactersManager.h"
#include "GameMode/Helpers/EventsManager.h"
#include "GameMode/Helpers/MoneyManager.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Screens/CharacterMenuStorage.h"
#include "UI/ButtonCreateChooseScreen.h"
#include "UI/ConfirmationWindow.h"
#include "UI/MoneyPanel.h"
#include "UI/Cards/CharacterCardMainScreen.h"
#include "UI/Screens/BackgroundMenu.h"
#include "UI/Screens/CharacterMenuShop.h"
#include "UI/Screens/EventScreen.h"
#include "UI/Screens/Guide.h"
#include "UI/Screens/SettingsScreen.h"


void UMainScreen::NativeConstruct()
{
	Super::NativeConstruct();
	InitializeReferences();
	BindDelegates();
	CreateSlots();
	CreateMoneyPanel();
	if (IsFirstLoad) CreateGuide();
}


void UMainScreen::SetIsFirstLoad(bool bIsFirstLoad)
{
	IsFirstLoad = bIsFirstLoad;
}


void UMainScreen::InitializeReferences()
{
	GameMode = Cast<ASilentWaifuGameMode>(UGameplayStatics::GetGameMode(this));
	if (!GameMode) return;
	MoneyManager = GameMode->MoneyManager;
	CharactersManager = GameMode->CharactersManager;
	BackgroundManager = GameMode->BackgroundManager;
	EventsManager = GameMode->EventsManager;
}


void UMainScreen::BindDelegates()
{
	if (!MoneyManager || !BackgroundManager || !EventsManager) return;
	BackgroundManager->OnCurrentBackgroundSetDelegate.AddDynamic(this, &UMainScreen::SetBackground);
	Button_Storage->OnClicked.AddDynamic(this, &UMainScreen::CreateStorage);
	Button_Shop->OnClicked.AddDynamic(this, &UMainScreen::CreateShop);
	Button_BackgroundsMenu->OnClicked.AddDynamic(this, &UMainScreen::CreateBgMenu);
	Button_Settings->OnClicked.AddDynamic(this, &UMainScreen::CreateSettings);
	Button_Event->OnClicked.AddDynamic(this, &UMainScreen::CreateEventScreen);
	OnCharacterSpawnedDelegate.AddDynamic(this, &UMainScreen::RemoveButton);
	OnCharacterRemovedDelegate.AddDynamic(this, &UMainScreen::RemoveCharacter);
	EventsManager->HasEventStartedDelegate.AddDynamic(this, &UMainScreen::HandleEvent);
}


void UMainScreen::CreateGuide()
{
	if (!GuideClass) return;
	GuideRef = Cast<UGuide>(CreateWidget(this, GuideClass));
	if (!GuideRef) return;
	GuideRef->AddToViewport(10);
}

void UMainScreen::CreateConfirmationWindow(bool IsEvent)
{
	if (!WidgetReferences || !WidgetReferences->ConfirmationWindowClass) return;
	WidgetReferences->ConfirmationWindowRef = Cast<UConfirmationWindow>(CreateWidget(GetWorld(), WidgetReferences->ConfirmationWindowClass));
	if (!WidgetReferences->ConfirmationWindowRef) return;
	WidgetReferences->ConfirmationWindowRef->SetIsEvent(IsEvent);
	WidgetReferences->ConfirmationWindowRef->AddToViewport(4);
	WidgetReferences->ConfirmationWindowRef->OnConfirmedDelegate.AddDynamic(this, &UMainScreen::RemoveConfirmationWindow);
	WidgetReferences->ConfirmationWindowRef->OnCanceledDelegate.AddDynamic(this, &UMainScreen::RemoveConfirmationWindow);
}


void UMainScreen::RemoveConfirmationWindow()
{
	if (!WidgetReferences || !WidgetReferences->ConfirmationWindowRef) return;
	WidgetReferences->ConfirmationWindowRef->RemoveFromParent();
	WidgetReferences->ConfirmationWindowRef = nullptr;
}


void UMainScreen::CreateStorage()
{
	if (!WidgetReferences || !WidgetReferences->StorageScreenClass) return;
	WidgetReferences->StorageScreenRef = Cast<UCharacterMenuStorage>(CreateWidget(GetWorld(), WidgetReferences->StorageScreenClass));
	if (!WidgetReferences->StorageScreenRef) return;
	WidgetReferences->StorageScreenRef->AddToViewport(1);
}


void UMainScreen::CreateShop()
{
	if (!WidgetReferences || !WidgetReferences->ShopScreenClass) return;
	WidgetReferences->ShopScreenRef = Cast<UCharacterMenuShop>(CreateWidget(GetWorld(), WidgetReferences->ShopScreenClass));
	if (!WidgetReferences->ShopScreenRef) return;
	WidgetReferences->ShopScreenRef->AddToViewport(1);
}


void UMainScreen::CreateBgMenu()
{
	if (!WidgetReferences || !WidgetReferences->BackgroundMenuClass || !BackgroundManager) return;
	WidgetReferences->BackgroundMenuRef = Cast<UBackgroundMenu>(CreateWidget(GetWorld(), WidgetReferences->BackgroundMenuClass));
	if (!WidgetReferences->BackgroundMenuRef) return;
	WidgetReferences->BackgroundMenuRef->AddToViewport(1);
}


void UMainScreen::CreateSettings()
{
	if (!WidgetReferences || !WidgetReferences->SettingsScreenClass) return;
	WidgetReferences->SettingsScreenRef = Cast<USettingsScreen>(CreateWidget(GetWorld(), WidgetReferences->SettingsScreenClass));
	if (!WidgetReferences->SettingsScreenRef) return;
	WidgetReferences->SettingsScreenRef->AddToViewport(1);
}


void UMainScreen::SetBackground(UTexture2D* CurrentBackground)
{
	if (!CurrentBackground) return;
	Image_Background->SetBrushFromTexture(CurrentBackground);
	OnBackgroundSetDelegate.Broadcast();
}


void UMainScreen::CreateEventScreen()
{
	if (!WidgetReferences || !WidgetReferences->EventScreenClass) return;
	WidgetReferences->EventScreenRef = Cast<UEventScreen>(CreateWidget(GetWorld(), WidgetReferences->EventScreenClass));
	if (!WidgetReferences->EventScreenRef) return;
	WidgetReferences->EventScreenRef->AddToViewport(1);
	WidgetReferences->EventScreenRef->Init(101);//!!!!!!!!!!! Look at the required character's id
}


void UMainScreen::CreateSlots()
{
	for (int i = 0 ; i < AmountOfSlots; i++)
	{
		UVerticalBox* VB = NewObject<UVerticalBox>(this);
		UHorizontalBoxSlot* HBSlot = Cast<UHorizontalBoxSlot>(HorizontalBox_CharacterSlots->AddChild(VB));
		if (HBSlot)
		{
			HBSlot->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
		}
	}
	FillSlots();
}


void UMainScreen::FillSlots()
{
	if (!CharactersManager) return;
	int SlotNumber = 0;
	for (const auto& CharacterSlot : HorizontalBox_CharacterSlots->GetAllChildren())
	{
		bool IsSpawned = CharactersManager->GetTakenPositions().FindRef(SlotNumber);
		if (!IsSpawned)
		{
			Cast<UVerticalBox>(CharacterSlot)->AddChild(CreateButton(SlotNumber));
		}
		else
		{
			Cast<UVerticalBox>(CharacterSlot)->AddChild(CreateCharacterCard(SlotNumber));
		}
		SlotNumber++;
	}
}


UButtonCreateChooseScreen* UMainScreen::CreateButton(const int SpawnPosition) const
{
	if (!WidgetReferences || !WidgetReferences->ButtonCreateChooseScreenClass) return nullptr;
	UButtonCreateChooseScreen* Button = CreateWidget<UButtonCreateChooseScreen>(GetWorld(), WidgetReferences->ButtonCreateChooseScreenClass);
	if (!Button) return nullptr;
	Button->SetSpawnPosition(SpawnPosition);
	return Button;
}


UCharacterCardMainScreen* UMainScreen::CreateCharacterCard(const int SpawnPosition) const
{
	if (!WidgetReferences || !WidgetReferences->CharacterCardMainScreenClass || !CharactersManager) return nullptr;
	UCharacterCardMainScreen* CharacterCard = CreateWidget<UCharacterCardMainScreen>(GetWorld(), WidgetReferences->CharacterCardMainScreenClass);
	if (!CharacterCard) return nullptr;
	int CharacterId = INDEX_NONE;
	for (const auto& Character : CharactersManager->GetAvailableCharacters())
	{
		if (Character.Value.Position == SpawnPosition)
		{
			CharacterId = Character.Value.CharacterId;
			break;
		}
	}
	CharacterCard->CreateCard(CharacterId);
	return CharacterCard;
}


void UMainScreen::RemoveButton(const int Position)
{
	UVerticalBox* VB_Slot = Cast<UVerticalBox>(HorizontalBox_CharacterSlots->GetChildAt(Position));
	if (!VB_Slot) return;
	VB_Slot->RemoveChildAt(0);
	VB_Slot->AddChild(CreateCharacterCard(Position));
}


void UMainScreen::RemoveCharacter(const int Position)
{
	UVerticalBox* VB_Slot = Cast<UVerticalBox>(HorizontalBox_CharacterSlots->GetChildAt(Position));
	if (!VB_Slot) return;
	VB_Slot->RemoveChildAt(0);
	VB_Slot->AddChild(CreateButton(Position));
}


void UMainScreen::CreateMoneyPanel()
{
	if (!WidgetReferences || !WidgetReferences->MoneyPanelClass) return;
	WidgetReferences->MoneyPanelRef = Cast<UMoneyPanel>(CreateWidget(GetWorld(), WidgetReferences->MoneyPanelClass));
	if (!WidgetReferences->MoneyPanelRef) return;
	WidgetReferences->MoneyPanelRef->AddToViewport(1);
}


void UMainScreen::HandleEvent(const bool HasEventStarted)
{
	if (HasEventStarted) Button_Event->SetVisibility(ESlateVisibility::Visible);
	else Button_Event->SetVisibility(ESlateVisibility::Hidden);
}
