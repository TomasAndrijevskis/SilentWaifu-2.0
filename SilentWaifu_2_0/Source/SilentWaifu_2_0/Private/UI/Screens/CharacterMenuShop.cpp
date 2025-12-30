
#include "UI/Screens/CharacterMenuShop.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"
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
	OnShopNeedUpdateDelegate.AddUniqueDynamic(this,&UCharacterMenuShop::UpdateShop);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UCharacterMenuShop::CreateTimeCountdown,1, true, 0.f);
	CheckUpdateAfterShutdown();
}


void UCharacterMenuShop::UpdateShop()
{
	if (!CharactersManager) return;
	HorizontalBox_Shop->ClearChildren();
	CharactersManager->GetShopCharacters().Empty();
	CreateCharacterMenu();
	CanUpdateShop = false;
}


void UCharacterMenuShop::RemoveCharacterMenu()
{
	if (!WidgetReferences || !WidgetReferences->ShopScreenRef) return;
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	WidgetReferences->ShopScreenRef->RemoveFromParent();
	WidgetReferences->ShopScreenRef = nullptr;
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
		}
		else MaxRandomNumber -= 5;
	}
	return OutCharacters;
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
		if (Character->Rarity == GetCharacterRarity() && Character->CharacterId != 1) CharacterIds.AddUnique(Character->CharacterId);
	}

	int NumberOfPossibleCharacters = CharacterIds.Num();
	if (NumberOfPossibleCharacters == 0) return GetCharacter();
	if (NumberOfPossibleCharacters == 1) return CharacterIds[0];
	int CharacterIndex = FMath::RandRange(0, NumberOfPossibleCharacters - 1);
	return CharacterIds[CharacterIndex];
}


int UCharacterMenuShop::GetCharacterRarity()
{
	if (!RarityDataTable) return 0;
	TArray<FCharacterRarities*> Rarities;
	RarityDataTable->GetAllRows(TEXT("Find Rarity Rows"), Rarities);
	if (Rarities.Num() == 0) return 0;
	TArray<int> DropChances;
	for (const auto RowArray : Rarities)
	{
		DropChances.Add(RowArray->DropChance);
	}
	int RandomNumber = FMath::RandRange(1, MaxRandomNumber);
	for (int RarityId = DropChances.Num() - 1; RarityId > 0; RarityId--)
	{
		if (RandomNumber <= DropChances[RarityId]) return RarityId;
	}
	return 0;
}


void UCharacterMenuShop::CreateTimeCountdown()
{
	FTimespan CurrentTime = FDateTime().Now().GetTimeOfDay();
	if (CurrentTime > FTimespan(11, 59, 59)) UpdateTime = FTimespan(23, 59, 59);
	else UpdateTime = FTimespan(11, 59, 59);
	
	FTimespan TimeLeft = UpdateTime - CurrentTime;
	FString FormatedTime = TimeLeft.GetDuration().ToString(TEXT("%h:%m:%s"));
	if (FormatedTime.StartsWith(TEXT("+"))) FormatedTime.RemoveAt(0);
	Text_RemainingTime->SetText(FText::FromString(FormatedTime));
	CheckLiveShopUpdate(FormatedTime);
}


void UCharacterMenuShop::CheckLiveShopUpdate(const FString& TimeLeft)
{
	FString ZeroTime = TEXT("00:00:00");
	if (ZeroTime == TimeLeft && !CanUpdateShop)
	{
		OnShopNeedUpdateDelegate.Broadcast();
		CanUpdateShop = true;
	}
}


void UCharacterMenuShop::CheckUpdateAfterShutdown()
{
	if (!GameMode) return;
	FDateTime ShutdownTime = GameMode->GetShutdownTime();
	FDateTime CurrentTime = FDateTime::Now();
	if (ShutdownTime.GetDayOfYear() != CurrentTime.GetDayOfYear())
	{
		OnShopNeedUpdateDelegate.Broadcast();
		CanUpdateShop = true;
		GameMode->SetShutdownTime(CurrentTime);
		return;
	}
	if (ShutdownTime.GetHour() < 12 && CurrentTime.GetHour() >= 12)
	{
		OnShopNeedUpdateDelegate.Broadcast();
		CanUpdateShop = true;
		GameMode->SetShutdownTime(CurrentTime);
	}
}

