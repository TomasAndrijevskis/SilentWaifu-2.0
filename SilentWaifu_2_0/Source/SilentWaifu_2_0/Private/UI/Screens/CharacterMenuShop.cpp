
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
	if (!CharactersManager) return;
	if (!WidgetReferences || !WidgetReferences->LimitIncreaseCardClass) return;
	WidgetReferences->LimitIncreaseCardRef = Cast<ULimitIncreaseCard>(CreateWidget(GetWorld(), WidgetReferences->LimitIncreaseCardClass));
	if (!WidgetReferences->LimitIncreaseCardRef) return;
	HorizontalBox_Shop->AddChild(WidgetReferences->LimitIncreaseCardRef);
	WidgetReferences->LimitIncreaseCardRef->CreateCard();
	if (CharactersManager->GetShopCharacters().IsEmpty())
	{
		const TArray<int> CharacterIds = GetRandomCharacters();
		CreateShop(CharacterIds);
		CharactersManager->SetShopCharacters(CharacterIds);
	}
	else
	{
		CreateShop(CharactersManager->GetShopCharacters());
	}
}


void UCharacterMenuShop::CreateShop(TArray<int> Characters)
{
	int i = 1;
	for (const int CharacterId : Characters)
	{
		if (!WidgetReferences || !WidgetReferences->ShopCharacterCardClass) return;
		WidgetReferences->ShopCharacterCardRef = Cast<UCharacterCardShop>(CreateWidget(GetWorld(), WidgetReferences->ShopCharacterCardClass));
		if (!WidgetReferences->ShopCharacterCardRef) return;
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





