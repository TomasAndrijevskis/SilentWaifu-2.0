
#include "UI/Screens/CharacterMenuShop.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "DataTables/CharacterRarities.h"
#include "GameMode/SilentWaifuGameMode.h"
#include "GameMode/Helpers/CharactersManager.h"
#include "UI/WidgetReferenceDataAsset.h"
#include "UI/Cards/CharacterCardShop.h"
#include "UI/Cards/LimitIncreaseCard.h"


void UCharacterMenuShop::NativeConstruct()
{
	Super::NativeConstruct();
	Button_UpdateShop->OnClicked.AddDynamic(this,&UCharacterMenuShop::UpdateShop);
}


void UCharacterMenuShop::UpdateShop()
{
	if (!CharactersManager) return;
	HorizontalBox_Shop->ClearChildren();
	CharactersManager->GetShopCharacters().Empty();
	CreateCharacterMenu();
}


void UCharacterMenuShop::CreateCharacterMenu()
{
	if (!CharactersManager || !GameMode) return;
	if (!WidgetReferences || !WidgetReferences->LimitIncreaseCardClass) return;
	WidgetReferences->LimitIncreaseCardRef = Cast<ULimitIncreaseCard>(CreateWidget(GetWorld(), WidgetReferences->LimitIncreaseCardClass));
	if (!WidgetReferences->LimitIncreaseCardRef) return;
	HorizontalBox_Shop->AddChild(WidgetReferences->LimitIncreaseCardRef);
	WidgetReferences->LimitIncreaseCardRef->CreateCard();
	if (CharactersManager->GetShopCharacters().IsEmpty())
	{
		TArray<int> CharacterIds;
		GetRandomCharacters(CharacterIds);
		CreateShop(CharacterIds);
		CharactersManager->SetShopCharacters(CharacterIds);
		GameMode->OnShopCreatedDelegate.Broadcast();
	}
	else
	{
		CreateShop(CharactersManager->GetShopCharacters());
	}
}


void UCharacterMenuShop::CreateShop(TArray<int> Characters)
{
	for (const int CharacterId : Characters)
	{
		if (!WidgetReferences || !WidgetReferences->ShopCharacterCardClass) return;
		WidgetReferences->ShopCharacterCardRef = Cast<UCharacterCardShop>(CreateWidget(GetWorld(), WidgetReferences->ShopCharacterCardClass));
		if (!WidgetReferences->ShopCharacterCardRef) return;
		HorizontalBox_Shop->AddChild(WidgetReferences->ShopCharacterCardRef);
		WidgetReferences->ShopCharacterCardRef->CreateCard(CharacterId);
	}
}


TArray<int>& UCharacterMenuShop::GetRandomCharacters(TArray<int>& OutCharacters)
{
	OutCharacters.Empty();
	if (!CharacterDataTable) return OutCharacters;
	int OriginalMaxNumber = MaxRandomNumber;
	while (OutCharacters.Num() != 4)
	{
		int NewShopCharacterID = GetCharacter();
		if (!OutCharacters.Contains(NewShopCharacterID))
		{
			MaxRandomNumber = OriginalMaxNumber;
			OutCharacters.Add(NewShopCharacterID);
			UE_LOG(LogTemp, Warning, TEXT("Added to shop: %i"), NewShopCharacterID);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Already in shop: %i"), NewShopCharacterID);
			MaxRandomNumber -= 5;	
		}
	}
	return OutCharacters;
}


int UCharacterMenuShop::GetCharacterRarity()
{
	if (!CharacterDataTable || !RarityDataTable) return 0;
	TArray<FCharacterRarities*> Rarities;
	RarityDataTable->GetAllRows(TEXT("Find Rarity Rows"), Rarities);
	if (Rarities.Num() == 0) return 0;
	TArray<int> DropChances;
	for (const auto RowArray : Rarities)
	{
		DropChances.Add(RowArray->DropChance);
	}
	int RandomNumber = FMath::RandRange(1, MaxRandomNumber);
	//UE_LOG(LogTemp, Warning, TEXT("Random Number: %i"), RandomNumber);
	for (int RarityId = DropChances.Num() - 1; RarityId >= 0; RarityId--)
	{
		if (RandomNumber <= DropChances[RarityId])
		{
			return RarityId;
		}
	}
	return 0;
}


int UCharacterMenuShop::GetCharacter()
{
	if (!CharacterDataTable) return 0;
	TArray<FCharacterData*> Characters;
	CharacterDataTable->GetAllRows(TEXT("Find Characters"), Characters);
	if (Characters.Num() == 0) return 0;
	TArray<int> CharacterIds;
	for (const auto Character : Characters)
	{
		if (Character->Rarity == GetCharacterRarity() && Character->CharacterId != 1)
		{
			CharacterIds.AddUnique(Character->CharacterId);
		}
	}

	int NumberOfPossibleCharacters = CharacterIds.Num();
	if (NumberOfPossibleCharacters == 0) return GetCharacter(); // try again
	if (NumberOfPossibleCharacters == 1) return CharacterIds[0];
	int CharacterIndex = FMath::RandRange(0, NumberOfPossibleCharacters - 1);
	//UE_LOG(LogTemp, Warning, TEXT("Chosen Character index: %i"), CharacterIndex);
	//UE_LOG(LogTemp, Warning, TEXT("Chosen Character: %i"), CharacterIds[CharacterIndex]);
	return CharacterIds[CharacterIndex];
}



