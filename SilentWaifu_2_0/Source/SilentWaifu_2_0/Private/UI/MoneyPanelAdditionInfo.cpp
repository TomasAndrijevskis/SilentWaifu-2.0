
#include "UI/MoneyPanelAdditionInfo.h"
#include "Character/CharacterTemplate.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"


void UMoneyPanelAdditionInfo::NativeConstruct()
{
	Super::NativeConstruct();
	SetOverallMoney();
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UMoneyPanelAdditionInfo::Countdown, 1, true);
}


void UMoneyPanelAdditionInfo::Countdown()
{
	if (AliveTime > 0) AliveTime--;
	else OnTimerFinishedDelegate.Broadcast();
}


void UMoneyPanelAdditionInfo::ClearTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}


void UMoneyPanelAdditionInfo::SetOverallMoney()
{
	TArray<AActor*> OutArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACharacterTemplate::StaticClass(), OutArray);
	for (const auto& Character : OutArray)
	{
		if (IsValid(Cast<ACharacterTemplate>(Character)))
		{
			OverallMoney += Cast<ACharacterTemplate>(Character)->GetMoneyPerSecond();
		}
	}
	SetText();
}


void UMoneyPanelAdditionInfo::SetText()
{
	Text_OverallMoney->SetText(FText::FromString(FString::FromInt(OverallMoney)));
}
