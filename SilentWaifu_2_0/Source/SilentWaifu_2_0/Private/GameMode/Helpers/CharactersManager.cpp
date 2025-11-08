
#include "GameMode/Helpers/CharactersManager.h"
#include "Character/CharacterTemplate.h"
#include "GameMode/SilentWaifuGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGame/SavedCharactersData.h"


void UCharactersManager::Init()
{
	GameMode = Cast<ASilentWaifuGameMode>(UGameplayStatics::GetGameMode(this));
	OnCharacterUpgradeDelegate.AddDynamic(this, &UCharactersManager::UpdateCharacterLevel);
	OnCharacterAddedDelegate.AddDynamic(this, &UCharactersManager::AddAvailableCharacter);
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
	TArray<TPair<int, FSavedCharactersData>> SortedCharacters = AvailableCharacters.Array();
	SortedCharacters.Sort([](const auto& A, const auto& B)
	{
		return A.Value.CharacterId < B.Value.CharacterId;
	});
	return SortedCharacters;
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