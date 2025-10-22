
#include "UI/UnlockCharacterButton.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "GameMode/SilentWaifuGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGame/SavedCharactersData.h"
#include "SaveGame/SilentWaifuGameInstance.h"


void UUnlockCharacterButton::NativeConstruct()
{
	Super::NativeConstruct();
	SetGameInstance();
	SetGameMode();
	OnCharacterUnlockedDelegate.AddDynamic(this, &UUnlockCharacterButton::UpdateCharacterUnlockStatus);
	OnCharacterUnlockedDelegate.AddDynamic(GameMode, &ASilentWaifuGameMode::SortCharactersById);
	UpdateCharacterUnlockStatus();
	Text_CharacterId->SetText(FText::FromString(FString::FromInt(CharacterId)));
}


void UUnlockCharacterButton::UpdateCharacterUnlockStatus()
{
	if (!GameInstance->IsCharacterUnlocked(CharacterClass))
	{
		Button_UnlockCharacter->OnClicked.Clear();
		Button_UnlockCharacter->OnClicked.AddDynamic(this, &UUnlockCharacterButton::UnlockCharacter);
	}
	else
	{
		Button_UnlockCharacter->SetIsEnabled(false);
	}
}


void UUnlockCharacterButton::UnlockCharacter()
{
	if (!GameInstance)
	{
		return;
	}
	if (GameMode->HasEnoughMoney(Cost))
	{
		FSavedCharactersData Data;
		Data.CharacterClass = CharacterClass;
		Data.bIsOnScreen = false;
		Data.CharacterId = CharacterId;
		GameMode->OnCharacterAddedDelegate.Broadcast(CharacterId, Data);
		GameMode->DecreaseMoney(Cost);
		OnCharacterUnlockedDelegate.Broadcast();
	}
}


void UUnlockCharacterButton::SetGameInstance()
{
	GameInstance = Cast<USilentWaifuGameInstance>(UGameplayStatics::GetGameInstance(this));
}


void UUnlockCharacterButton::SetGameMode()
{
	GameMode = Cast<ASilentWaifuGameMode>(UGameplayStatics::GetGameMode(this));
}

