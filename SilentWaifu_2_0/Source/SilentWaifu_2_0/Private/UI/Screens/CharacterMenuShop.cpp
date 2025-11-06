
#include "UI/Screens/CharacterMenuShop.h"
#include "Components/HorizontalBox.h"
#include "Components/VerticalBox.h"
#include "GameMode/SilentWaifuGameMode.h"
#include "GameMode/Helpers/CharactersManager.h"
#include "UI/WidgetReferenceDataAsset.h"
#include "UI/Cards/CharacterCardShop.h"
#include "UI/Cards/LimitIncreaseCard.h"


void UCharacterMenuShop::CreateCharacterMenu()
{
	if (!GameMode) return;
	if (WidgetReferences->LimitIncreaseCardClass)
	{
		WidgetReferences->LimitIncreaseCardRef = Cast<ULimitIncreaseCard>(CreateWidget(GetWorld(), WidgetReferences->LimitIncreaseCardClass));
		HorizontalBox_Shop->AddChild(WidgetReferences->LimitIncreaseCardRef);
		WidgetReferences->LimitIncreaseCardRef->CreateCard();
		
		if (GameMode->CharactersManager->GetShopCharacters().IsEmpty())
		{
			const TArray<int> CharacterIds = GetRandomCharacters();
			CreateShop(CharacterIds);
			GameMode->CharactersManager->SetShopCharacters(CharacterIds);
		}
		else
		{
			CreateShop(GameMode->CharactersManager->GetShopCharacters());
		}
	}
}



void UCharacterMenuShop::CreateShop(TArray<int> Characters)
{
	int i = 1;
	for (const int CharacterId : Characters)
	{
		WidgetReferences->ShopCharacterCardRef = Cast<UCharacterCardShop>(CreateWidget(GetWorld(), WidgetReferences->ShopCharacterCardClass));
		HorizontalBox_Shop->AddChild(WidgetReferences->ShopCharacterCardRef);
		WidgetReferences->ShopCharacterCardRef->CreateCard(CharacterId);
		i++;
	}
}


int UCharacterMenuShop::GetCharactersCount() const
{
	if (!CharacterDataTable) return 0;
	return CharacterDataTable->GetRowMap().Num();
}


TArray<int> UCharacterMenuShop::GetRandomCharacters() const
{
	if (!CharacterDataTable) return TArray<int>();
	const int CharactersCount = GetCharactersCount();
	TArray<int> Characters;

	while (Characters.Num() != 4)
	{
		Characters.AddUnique(FMath::RandRange(2, CharactersCount));
	}
	
	return Characters;
}





