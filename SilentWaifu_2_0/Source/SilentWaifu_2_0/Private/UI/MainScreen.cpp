
#include "UI/MainScreen.h"
#include "Components/TextBlock.h"
#include "GameMode/SilentWaifuGameMode.h"
#include "Kismet/GameplayStatics.h"


void UMainScreen::NativeConstruct()
{
	Super::NativeConstruct();
	//UE_LOG(LogTemp, Warning, TEXT("Main Screen Constructed"));
	GameMode = Cast<ASilentWaifuGameMode>(UGameplayStatics::GetGameMode(this));
	if (!GameMode)
	{
		return;
	}
	GameMode->OnMoneyChangedDelegate.AddDynamic(this, &UMainScreen::UpdateMoney);
}


void UMainScreen::UpdateMoney(int const Money)
{
	Text_CurrentMoney->SetText(FText::FromString(FString::FromInt(Money)));
	//UE_LOG(LogTemp, Error, TEXT("Money updated"));
}
