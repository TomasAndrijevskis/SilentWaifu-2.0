
#include "UI/Cards/CardBase.h"
#include "Components/Button.h"
#include "GameMode/SilentWaifuGameMode.h"
#include "Kismet/GameplayStatics.h"


void UCardBase::NativeConstruct()
{
	Super::NativeConstruct();
	GameMode = Cast<ASilentWaifuGameMode>(UGameplayStatics::GetGameMode(this));
	if (!GameMode) return;
	MoneyManager = GameMode->MoneyManager;
	Button_Action->OnClicked.AddDynamic(this, &UCardBase::Action);
}

