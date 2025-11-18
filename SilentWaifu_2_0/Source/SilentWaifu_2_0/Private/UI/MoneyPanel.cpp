
#include "UI/MoneyPanel.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"
#include "GameMode/SilentWaifuGameMode.h"
#include "GameMode/Helpers/MoneyManager.h"
#include "Kismet/GameplayStatics.h"
#include "UI/MoneyPanelAdditionInfo.h"
#include "UI/WidgetReferenceDataAsset.h"


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
	Button_Action->OnClicked.AddUniqueDynamic(this, &UMoneyPanel::CreateAdditionPanel);
}


void UMoneyPanel::UpdateCurrentMoney(int const Money)
{
	Text_CurrentMoney->SetText(FText::FromString(FString::FromInt(Money)));
}


void UMoneyPanel::UpdateMaxMoney(int const Money)
{
	Text_MaxMoney->SetText(FText::FromString(FString::FromInt(Money)));
}


void UMoneyPanel::CreateAdditionPanel()
{
	if (!WidgetReferences || !WidgetReferences->MoneyPanelAdditionInfoClass) return;
	WidgetReferences->MoneyPanelAdditionInfoRef = Cast<UMoneyPanelAdditionInfo>(CreateWidget(GetWorld(), WidgetReferences->MoneyPanelAdditionInfoClass));
	if (!WidgetReferences->MoneyPanelAdditionInfoRef) return;
	HorizontalBox_AdditionalInfo->AddChild(WidgetReferences->MoneyPanelAdditionInfoRef);
	WidgetReferences->MoneyPanelAdditionInfoRef->OnTimerFinishedDelegate.AddUniqueDynamic(this, &UMoneyPanel::RemoveAdditionalPanel);
	RebindButtonAction(true);
}


void UMoneyPanel::RemoveAdditionalPanel()
{
	if (!WidgetReferences || !WidgetReferences->MoneyPanelAdditionInfoRef) return;
	WidgetReferences->MoneyPanelAdditionInfoRef->ClearTimer();
	WidgetReferences->MoneyPanelAdditionInfoRef = nullptr;
	HorizontalBox_AdditionalInfo->ClearChildren();
	RebindButtonAction(false);
}


void UMoneyPanel::RebindButtonAction(const bool DoesPanelExists)
{
	DoesPanelExists ?
		(Button_Action->OnClicked.Clear(),
		Button_Action->OnClicked.AddDynamic(this, &UMoneyPanel::RemoveAdditionalPanel))
	:
		(Button_Action->OnClicked.Clear(),
		Button_Action->OnClicked.AddDynamic(this, &UMoneyPanel::CreateAdditionPanel));
}
