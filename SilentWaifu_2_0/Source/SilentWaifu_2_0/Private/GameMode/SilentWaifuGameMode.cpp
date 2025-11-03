
#include "GameMode/SilentWaifuGameMode.h"
#include "Blueprint/UserWidget.h"
#include "Character/CharacterTemplate.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGame/SilentWaifuGameInstance.h"
#include "UI/Screens/MainScreen.h"


void ASilentWaifuGameMode::BeginPlay()
{
	Super::BeginPlay();
	OnCharacterAddedDelegate.AddDynamic(this, &ASilentWaifuGameMode::AddAvailableCharacter);
	OnCharactersLoadedDelegate.AddDynamic(this, &ASilentWaifuGameMode::SpawnCharacters);
	GameInstance = Cast<USilentWaifuGameInstance>(UGameplayStatics::GetGameInstance(this));
	HandleGameLoad();
}


void ASilentWaifuGameMode::HandleGameLoad()
{
	if (!GameInstance) return;
	GameInstance->SetGameMode(this);
	GameInstance->LoadPositions();
	CreateMainScreenWidget();
	SetInputSettings();
	GameInstance->LoadMoney();
	GameInstance->LoadShop();
	OnCurrentMoneyChangedDelegate.AddDynamic(GameInstance, &USilentWaifuGameInstance::SaveCurrentMoney);
	OnMaxMoneyChangedDelegate.AddDynamic(GameInstance, &USilentWaifuGameInstance::SaveMaxMoney);
}


void ASilentWaifuGameMode::CreateMainScreenWidget()
{
	if (WidgetReferences->MainScreenClass)
	{
		WidgetReferences->MainScreenRef = Cast<UMainScreen>(CreateWidget(GetWorld(), WidgetReferences->MainScreenClass));
		if (WidgetReferences->MainScreenRef)
		{
			WidgetReferences->MainScreenRef->AddToViewport(0);
		}
	}
}


void ASilentWaifuGameMode::SetInputSettings() const
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(),0);
	PC->SetShowMouseCursor(true);
	FInputModeUIOnly InputMode;
	PC->SetInputMode(InputMode);
}


void ASilentWaifuGameMode::SpawnCharacters()
{
	for (auto Character : GetAvailableCharacters())
	{
		if (Character.Value.bIsOnScreen == true)
		{
			FActorSpawnParameters SpawnParameters;
			GetWorld()->SpawnActor<ACharacterTemplate>(Character.Value.CharacterClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParameters);
		}
	}
}


void ASilentWaifuGameMode::SpawnCharacter(const int CharacterId)
{
	FActorSpawnParameters SpawnParameters;
	GetWorld()->SpawnActor<ACharacterTemplate>(AvailableCharacters.FindRef(CharacterId).CharacterClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParameters);
	FSavedCharactersData* Data = AvailableCharacters.Find(CharacterId);
	Data->bIsOnScreen = true;
	Data->Position = CurrentSpawnPosition;
	AddTakenPosition(CurrentSpawnPosition, true);
	WidgetReferences->MainScreenRef->OnCharacterSpawnedDelegate.Broadcast(CurrentSpawnPosition);
	UE_LOG(LogTemp, Error, TEXT("Position: %i"), CurrentSpawnPosition);
}


void ASilentWaifuGameMode::RemoveCharacter(const int CharacterId)
{
	FSavedCharactersData* Data = AvailableCharacters.Find(CharacterId);
	TArray<AActor*> ActorsToRemove;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), Data->CharacterClass,ActorsToRemove);
	for (auto Actor : ActorsToRemove)
	{
		if (IsValid(Actor))
		{
			Actor->Destroy();
			Actor = nullptr;
		}
	}
	TakenPositions.Remove(Data->Position);
	Data->bIsOnScreen = false;
	WidgetReferences->MainScreenRef->OnCharacterRemovedDelegate.Broadcast(Data->Position);
	Data->Position = NULL;
}


void ASilentWaifuGameMode::IncreaseMoney(const int Money)
{
	if (CurrentMoney + Money < MaxMoney)
	{
		CurrentMoney += Money;
	}
	else
	{
		CurrentMoney = MaxMoney;
	}
	OnCurrentMoneyChangedDelegate.Broadcast(CurrentMoney);
}


void ASilentWaifuGameMode::DecreaseMoney(const int Money)
{
	CurrentMoney -= Money;
	OnCurrentMoneyChangedDelegate.Broadcast(CurrentMoney);
}


bool ASilentWaifuGameMode::HasEnoughMoney(const int Money) const
{
	if (CurrentMoney >= Money)
	{
		return true;
	}
	return false;
}


void ASilentWaifuGameMode::IncreaseMoneyLimit()
{
	MaxMoney += 200;
	OnMaxMoneyChangedDelegate.Broadcast(MaxMoney);
}


void ASilentWaifuGameMode::SetMaxMoney(const int NewMaxMoney)
{
	MaxMoney = NewMaxMoney;
	OnMaxMoneyChangedDelegate.Broadcast(MaxMoney);
}


TArray<TPair<int, FSavedCharactersData>> ASilentWaifuGameMode::GetSortedCharacters() const
{
	TArray<TPair<int, FSavedCharactersData>> SortedCharacters = AvailableCharacters.Array();
	SortedCharacters.Sort([](const auto& A, const auto& B)
	{
		return A.Value.CharacterId < B.Value.CharacterId;
	});
	return SortedCharacters;
}


void ASilentWaifuGameMode::AddTakenPosition(const int Key, const bool Value)
{
	TakenPositions.Add(Key, Value);
}


void ASilentWaifuGameMode::AddAvailableCharacter(int const Key, const FSavedCharactersData& Data)
{
	AvailableCharacters.Add(Key, Data);
}


TMap<int, FSavedCharactersData>& ASilentWaifuGameMode::GetAvailableCharacters()
{
	/*for (auto ch : AvailableCharacters)
	{
		UE_LOG(LogTemp, Error, TEXT("Character: %i"), ch.Value.CharacterId);
	}*/
	return AvailableCharacters;
}


TMap<int, bool>& ASilentWaifuGameMode::GetTakenPositions()
{
	return TakenPositions;
}


void ASilentWaifuGameMode::SetCurrentSpawnPosition(const int NewSpawnPosition)
{
	CurrentSpawnPosition = NewSpawnPosition;
}


void ASilentWaifuGameMode::SetShopCharacters(const TArray<int>& NewShopCharacters)
{
	ShopCharacters = NewShopCharacters;
}


TArray<int> ASilentWaifuGameMode::GetShopCharacters() const
{
	return ShopCharacters;
}