
#include "GameMode/Helpers/CharactersManager.h"
#include "Character/CharacterTemplate.h"
#include "GameMode/SilentWaifuGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGame/SavedCharactersData.h"


void UCharactersManager::Init(UDataTable* DataTable)
{
	GameMode = Cast<ASilentWaifuGameMode>(UGameplayStatics::GetGameMode(this));
	OnCharacterUpgradeDelegate.AddDynamic(this, &UCharactersManager::UpdateCharacterLevel);
	OnCharacterAddedDelegate.AddDynamic(this, &UCharactersManager::AddAvailableCharacter);
	CharacterDataTable = DataTable;
}


void UCharactersManager::SpawnCharacters()
{
	for (const auto& Character : GetAvailableCharacters())
	{
		if (Character.Value.bIsOnScreen == true)
		{
			FActorSpawnParameters SpawnParameters;
			ACharacterTemplate* Actor = GetWorld()->SpawnActor<ACharacterTemplate>(Character.Value.CharacterClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParameters);
			Actor->SetValues(Character.Value.Level, Character.Key);
		}
	}
}


void UCharactersManager::SpawnCharacter(const int CharacterId)
{
	const FActorSpawnParameters SpawnParameters;
	ACharacterTemplate* Actor = GetWorld()->SpawnActor<ACharacterTemplate>(AvailableCharacters.FindRef(CharacterId).CharacterClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParameters);
	FSavedCharactersData* Data = AvailableCharacters.Find(CharacterId);
	Actor->SetValues(Data->Level, CharacterId);
	Data->bIsOnScreen = true;
	Data->Position = CurrentSpawnPosition;
	AddTakenPosition(CurrentSpawnPosition, true);
	GameMode->OnCharacterSpawned(CurrentSpawnPosition);
	//UE_LOG(LogTemp, Error, TEXT("Position: %i"), CurrentSpawnPosition);
}


void UCharactersManager::RemoveCharacter(const int CharacterId)
{
	FSavedCharactersData* Data = AvailableCharacters.Find(CharacterId);
	TArray<AActor*> ActorsToRemove;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), Data->CharacterClass,ActorsToRemove);
	for (auto Actor : ActorsToRemove)
	{
		if (IsValid(Actor))
		{
			Actor->Destroy();
		}
	}
	TakenPositions.Remove(Data->Position);
	Data->bIsOnScreen = false;
	GameMode->OnCharacterRemovedDelegate(Data->Position);
	Data->Position = NULL;
}


void UCharactersManager::UpdateCharacterLevel(const int CharacterId)
{
	for (const auto& Character : GetAvailableCharacters())
	{
		if (Character.Key == CharacterId && Character.Value.bIsOnScreen == true)
		{
			Cast<ACharacterTemplate>(UGameplayStatics::GetActorOfClass(GetWorld(),Character.Value.CharacterClass))->UpdateLevel(Character.Value.Level);
		}
	}
}


TArray<TPair<int, FSavedCharactersData>> UCharactersManager::GetSortedCharacters() const
{
	TArray<TPair<int, FSavedCharactersData>> UnlockedCharacters = AvailableCharacters.Array();
	if (!CharacterDataTable) return UnlockedCharacters;
	TMap<int, int> CharactersRarities;
	for (const auto& Character : UnlockedCharacters)
	{
		const FName RowName = FName(*FString::FromInt(Character.Value.CharacterId));
		const FCharacterData* CharacterRow = CharacterDataTable->FindRow<FCharacterData>(RowName, TEXT("Find Character By Id"));
		if (!CharacterRow) continue;
		CharactersRarities.Add(Character.Value.CharacterId, CharacterRow->Rarity);
	}
	TArray<TPair<int, int>> SortedCharactersByRarity = CharactersRarities.Array();
	SortedCharactersByRarity.Sort([](const auto& A, const auto& B)
	{
		if (A.Value == B.Value)
		{
			return A.Key < B.Key;
		}
		return A.Value < B.Value;
	});
	TArray<TPair<int, FSavedCharactersData>> FinalSorted;
	for (const auto& Pair : SortedCharactersByRarity)
	{
		const int CharacterId = Pair.Key;
		const FSavedCharactersData* FoundData = AvailableCharacters.Find(CharacterId);
		if (FoundData)
		{
			FinalSorted.Add(TPair<int, FSavedCharactersData>(CharacterId, *FoundData));
		}
	}
	return FinalSorted;
}


bool UCharactersManager::IsCharacterUnlocked(const int CharacterId) const
{
	for (const auto& Character : AvailableCharacters)
	{
		if (Character.Value.CharacterId == CharacterId)
		{
			return true;
		}
	}
	return false;
}


void UCharactersManager::AddTakenPosition(const int Key, const bool Value)
{
	TakenPositions.Add(Key, Value);
}


void UCharactersManager::AddAvailableCharacter(int const Key, const FSavedCharactersData& Data)
{
	AvailableCharacters.Add(Key, Data);
}


TMap<int, FSavedCharactersData>& UCharactersManager::GetAvailableCharacters()
{
	return AvailableCharacters;
}


TMap<int, bool>& UCharactersManager::GetTakenPositions()
{
	return TakenPositions;
}


void UCharactersManager::SetCurrentSpawnPosition(const int NewSpawnPosition)
{
	CurrentSpawnPosition = NewSpawnPosition;
}


void UCharactersManager::SetShopCharacters(const TArray<int>& NewShopCharacters)
{
	ShopCharacters = NewShopCharacters;
}


TArray<int>& UCharactersManager::GetShopCharacters()
{
	return ShopCharacters;
}