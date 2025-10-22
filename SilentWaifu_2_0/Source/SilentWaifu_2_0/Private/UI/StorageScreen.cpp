
#include "UI/StorageScreen.h"

#include "Components/ScrollBox.h"
#include "Components/WrapBox.h"
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
	for (const auto Character : GameMode->GetAvailableCharacters())
	{
		UE_LOG(LogTemp, Warning, TEXT("Character %i created"), Character.Key);
		if (WidgetReferences->StorageCharacterCardClass)
		{
			WidgetReferences->StorageCharacterCardRef = Cast<UStorageCharacterCard>(CreateWidget(GetWorld(), WidgetReferences->StorageCharacterCardClass));
			WrapBox->AddChild(WidgetReferences->StorageCharacterCardRef);
			WidgetReferences->StorageCharacterCardRef->CreateCard(Character.Value.CharacterId);
		}
	}
}
