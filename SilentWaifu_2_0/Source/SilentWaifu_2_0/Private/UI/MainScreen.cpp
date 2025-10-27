
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
#include "UI/CharacterCardMainScreen.h"

void UMainScreen::NativeConstruct()
{
	Super::NativeConstruct();
	GameMode = Cast<ASilentWaifuGameMode>(UGameplayStatics::GetGameMode(this));
	if (!GameMode) return;
	GameMode->OnMoneyChangedDelegate.AddDynamic(this, &UMainScreen::UpdateMoney);
	Button_Storage->OnClicked.AddDynamic(this, &UMainScreen::CreateStorage);
	OnWindowStateChangedDelegate.AddDynamic(this, &UMainScreen::HandleWindowState);
	OnCharacterSpawnedDelegate.AddDynamic(this, &UMainScreen::RemoveButton);
	OnCharacterRemovedDelegate.AddDynamic(this, &UMainScreen::RemoveCharacter);
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
		OnWindowStateChangedDelegate.Broadcast(false);
	}
}


void UMainScreen::RemoveStorage()
{
	if (WidgetReferences->StorageScreenRef)
	{
		WidgetReferences->StorageScreenRef->RemoveFromParent();
		WidgetReferences->StorageScreenRef = nullptr;
		OnWindowStateChangedDelegate.Broadcast(true);
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
	FillSlots();
}


void UMainScreen::FillSlots()
{
	int SlotNumber = 0;
	for (const auto CharacterSlot : HorizontalBox_CharacterSlots->GetAllChildren())
	{
		bool IsSpawned = GameMode->GetTakenPositions().FindRef(SlotNumber);
		UE_LOG(LogTemp, Error, TEXT("is spawned: %i"), IsSpawned);
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
	UButtonCreateChooseScreen* Button = CreateWidget<UButtonCreateChooseScreen>(GetWorld(), WidgetReferences->ButtonCreateChooseScreenClass);
	if (!Button) return nullptr;
	Button->SetSpawnPosition(SpawnPosition);
	return Button;
}


UCharacterCardMainScreen* UMainScreen::CreateCharacterCard(const int SpawnPosition) const
{
	UCharacterCardMainScreen* CharacterCard = CreateWidget<UCharacterCardMainScreen>(GetWorld(), WidgetReferences->CharacterCardMainScreenClass);
	if (!CharacterCard) return nullptr;

	int CharacterId = NULL;
	for (const auto Character : GameMode->GetAvailableCharacters())
	{
		if (Character.Value.Position == SpawnPosition)
		{
			CharacterId = Character.Value.CharacterId;
			UE_LOG(LogTemp, Error, TEXT("CreateCharacterCard||CharacterId: %i"), CharacterId);
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


void UMainScreen::HandleBlur(const float BlurStrength)
{
	BackgroundBlur->SetBlurStrength(BlurStrength);
}
