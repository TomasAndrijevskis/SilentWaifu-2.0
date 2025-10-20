
#include "UI/UnlockCharacterButton.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGame/SavedCharactersData.h"
#include "SaveGame/SilentWaifuGameInstance.h"


void UUnlockCharacterButton::NativeConstruct()
{
	Super::NativeConstruct();
	SetGameInstance();
	Button_UnlockCharacter->OnClicked.AddDynamic(this, &UUnlockCharacterButton::UnlockCharacter);
}


void UUnlockCharacterButton::UnlockCharacter()
{
	if (!GameInstance)
	{
		return;
	}
	FSavedCharactersData Data;
	Data.CharacterClass = CharacterClass;
	GameInstance->OnCharacterAddedDelegate.Broadcast(CharacterId, Data);
}


void UUnlockCharacterButton::SetGameInstance()
{
	GameInstance = Cast<USilentWaifuGameInstance>(UGameplayStatics::GetGameInstance(this));
}
