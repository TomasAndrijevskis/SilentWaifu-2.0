
#include "UI/CharacterAbilityCooldownPanel.h"
#include "Components/TextBlock.h"


void UCharacterAbilityCooldownPanel::Init(const FDateTime NewCooldownEndTime)
{
	CooldownEndTime = NewCooldownEndTime;
}


void UCharacterAbilityCooldownPanel::NativeConstruct()
{
	Super::NativeConstruct();
	EnableAbilityCooldownTimer();
	EnableAliveTimer();
}


void UCharacterAbilityCooldownPanel::EnableAbilityCooldownTimer()
{
	GetWorld()->GetTimerManager().SetTimer(AbilityCooldownTimerHandle, this, &UCharacterAbilityCooldownPanel::CreateAbilityCooldown, 1.f, true, 0);
}


void UCharacterAbilityCooldownPanel::EnableAliveTimer()
{
	GetWorld()->GetTimerManager().SetTimer(AliveTimerHandle, this, &UCharacterAbilityCooldownPanel::OnAliveTimerEnded, .1f, false, AliveTime);
}


void UCharacterAbilityCooldownPanel::OnAliveTimerEnded()
{
	GetWorld()->GetTimerManager().ClearTimer(AliveTimerHandle);
	OnCooldownEndedDelegate.Broadcast();
}


void UCharacterAbilityCooldownPanel::CreateAbilityCooldown()
{
	if (CooldownEndTime < FDateTime::Now()) SetCooldownText("Ready");
	else
	{
		FTimespan TimeLeft = CooldownEndTime - FDateTime::Now();
		FString FormatedTime = TimeLeft.GetDuration().ToString(TEXT("%h:%m:%s"));
		if (FormatedTime.StartsWith(TEXT("+"))) FormatedTime.RemoveAt(0);
		SetCooldownText(FormatedTime);
	}
}


void UCharacterAbilityCooldownPanel::SetCooldownText(const FString& Text)
{
	Text_AbilityCooldownValue->SetText(FText::FromString(Text));
}
