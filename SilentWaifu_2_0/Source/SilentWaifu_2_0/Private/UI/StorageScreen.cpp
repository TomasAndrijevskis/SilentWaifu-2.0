
#include "UI/StorageScreen.h"

#include "Components/ScrollBox.h"
#include "GameMode/SilentWaifuGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "UI/StorageCharacterCard.h"
#include "UI/WidgetReferenceDataAsset.h"


void UStorageScreen::NativeConstruct()
{
	Super::NativeConstruct();
	GameMode = Cast<ASilentWaifuGameMode>(UGameplayStatics::GetGameMode(this));
	CreateStorageCards();
}


void UStorageScreen::CreateStorageCards()
{
	if (!GameMode)
	{
		return;
	}
	for (auto Character : GameMode->GetAvailableCharacters())
	{
		if (WidgetReferences->StorageCharacterCardClass)
		{
			WidgetReferences->StorageCharacterCardRef = Cast<UStorageCharacterCard>(CreateWidget(GetWorld(), WidgetReferences->StorageCharacterCardClass));
			ScrollBox->AddChild(WidgetReferences->StorageCharacterCardRef);
		}
	}
}
