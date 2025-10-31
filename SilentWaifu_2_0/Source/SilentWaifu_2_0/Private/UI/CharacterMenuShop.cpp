
#include "UI/CharacterMenuShop.h"
#include "Components/HorizontalBox.h"
#include "GameMode/SilentWaifuGameMode.h"
#include "UI/WidgetReferenceDataAsset.h"
#include "UI/Cards/CharacterCardShop.h"


void UCharacterMenuShop::CreateCharacterMenu()
{
	if (!GameMode) return;

	if (WidgetReferences->ShopCharacterCardClass)
	{
		WidgetReferences->ShopCharacterCardRef = Cast<UCharacterCardShop>(CreateWidget(GetWorld(), WidgetReferences->ShopCharacterCardClass));
		HorizontalBox_Shop->AddChild(WidgetReferences->ShopCharacterCardRef);
		WidgetReferences->ShopCharacterCardRef->CreateLimitIncreaseCard();
		if (GameMode->GetShopCharacters().IsEmpty())
		{
			CreateNewShop();
		}
		else
		{
			CreateSavedShop();
		}
	}
}


void UCharacterMenuShop::CreateSavedShop()
{
	for (const int CharacterId : GameMode->GetShopCharacters())
	{
		WidgetReferences->ShopCharacterCardRef = Cast<UCharacterCardShop>(CreateWidget(GetWorld(), WidgetReferences->ShopCharacterCardClass));
		HorizontalBox_Shop->AddChild(WidgetReferences->ShopCharacterCardRef);
		WidgetReferences->ShopCharacterCardRef->CreateCard(CharacterId);
	}
}


void UCharacterMenuShop::CreateNewShop()
{
	const TArray<int> CharacterIds = GetRandomCharacters();
	for (const int CharacterId : CharacterIds)
	{
		WidgetReferences->ShopCharacterCardRef = Cast<UCharacterCardShop>(CreateWidget(GetWorld(), WidgetReferences->ShopCharacterCardClass));
		HorizontalBox_Shop->AddChild(WidgetReferences->ShopCharacterCardRef);
		WidgetReferences->ShopCharacterCardRef->CreateCard(CharacterId);
	}
	GameMode->SetShopCharacters(CharacterIds);
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





