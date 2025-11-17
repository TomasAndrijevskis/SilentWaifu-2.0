
#include "UI/MoneyPanel.h"
#include "Components/TextBlock.h"
#include "GameMode/SilentWaifuGameMode.h"
#include "GameMode/Helpers/MoneyManager.h"
#include "Kismet/GameplayStatics.h"


void UMoneyPanel::NativeConstruct()
{
	Super::NativeConstruct();
	GameMode = Cast<ASilentWaifuGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!GameMode) return;
	MoneyManager = GameMode->MoneyManager;
	BindDelegates();
}


void UMoneyPanel::BindDelegates()
{
	if (!MoneyManager) return;
	MoneyManager->OnCurrentMoneyChangedDelegate.AddDynamic(this, &UMoneyPanel::UpdateCurrentMoney);
	MoneyManager->OnMaxMoneyChangedDelegate.AddDynamic(this, &UMoneyPanel::UpdateMaxMoney);
}


void UMoneyPanel::UpdateCurrentMoney(int const Money)
{
	Text_CurrentMoney->SetText(FText::FromString(FString::FromInt(Money)));
}


void UMoneyPanel::UpdateMaxMoney(int const Money)
{
	Text_MaxMoney->SetText(FText::FromString(FString::FromInt(Money)));
}
