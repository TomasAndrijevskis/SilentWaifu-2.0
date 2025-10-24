
#include "UI/CharacterMenuBase.h"

#include "Components/Button.h"
#include "GameMode/SilentWaifuGameMode.h"
#include "Kismet/GameplayStatics.h"


void UCharacterMenuBase::NativeConstruct()
{
	Super::NativeConstruct();
	GameMode = Cast<ASilentWaifuGameMode>(UGameplayStatics::GetGameMode(this));
	CreateCharacterMenu();
	Button_Close->OnClicked.AddDynamic(this, &UCharacterMenuBase::RemoveCharacterMenu);
}
