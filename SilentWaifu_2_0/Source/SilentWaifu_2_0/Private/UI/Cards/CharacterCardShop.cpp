
#include "UI/Cards/CharacterCardShop.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "DataTables/CharacterData.h"
#include "GameMode/SilentWaifuGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGame/SilentWaifuGameInstance.h"


void UCharacterCardShop::NativeConstruct()
{
	Super::NativeConstruct();
	OnCardCreatedDelegate.AddDynamic(this, &UCharacterCardShop::SetGameInstance);
	OnCardCreatedDelegate.AddDynamic(this, &UCharacterCardShop::HandleState);
	OnCardCreatedDelegate.AddDynamic(this, &UCharacterCardShop::SetCharacterRow);
	OnCharacterUnlockedDelegate.AddDynamic(this, &UCharacterCardShop::HandleState);
}


void UCharacterCardShop::CreateLimitIncreaseCard()
{
	SetImage(Image_LimitIncreaseImage);
}


void UCharacterCardShop::SetImage(UTexture2D* NewImage)
{
	if (!NewImage) return;
	Image_CardImage->SetDesiredSizeOverride(ImageSize);
	Image_CardImage->SetBrushFromTexture(NewImage);
	OnCardCreatedDelegate.Broadcast();
}


void UCharacterCardShop::Action()
{
	UnlockCharacter();
}


void UCharacterCardShop::HandleState()
{
	if (!GameInstance) return;
	Button_Character->SetIsEnabled(!GameInstance->IsCharacterUnlocked(CharacterId));
}


void UCharacterCardShop::UnlockCharacter()
{
	if (!GameInstance) return;
	int Price = GetCharacterPrice();
	if (GameMode->HasEnoughMoney(Price))
	{
		if (!CharacterRow) return;
		FSavedCharactersData Data;
		Data.CharacterClass = CharacterRow->CharacterClass;
		Data.bIsOnScreen = false;
		Data.CharacterId = CharacterId;
		GameMode->OnCharacterAddedDelegate.Broadcast(CharacterId, Data);
		GameMode->DecreaseMoney(Price);
		OnCharacterUnlockedDelegate.Broadcast();
	}
}


void UCharacterCardShop::SetGameInstance()
{
	GameInstance = Cast<USilentWaifuGameInstance>(UGameplayStatics::GetGameInstance(this));
}


void UCharacterCardShop::SetCharacterRow()
{
	if (!CharacterDataTable) return;
	const FName RowName = FName(*FString::FromInt(CharacterId));
	CharacterRow = CharacterDataTable->FindRow<FCharacterData>(RowName, TEXT("Find Character By Id"));
}



int UCharacterCardShop::GetCharacterPrice() const
{
	if (!CharacterRow) return 0;
	return CharacterRow->Price;
}