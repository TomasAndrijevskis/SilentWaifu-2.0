
#include "GameMode/Helpers/BackgroundManager.h"


void UBackgroundManager::Init(UDataTable* DataTable)
{
	BackgroundDataTable = DataTable;
	OnBackgroundsLoadedDelegate.AddDynamic(this, &UBackgroundManager::HandleCurrentBackground);
	UE_LOG(LogTemp, Warning, TEXT("Background Manager Initialized"));
}


void UBackgroundManager::HandleCurrentBackground()
{
	if (!BackgroundDataTable) return;
	for (const auto& BG : UnlockedBackgrounds)
	{
		if (BG.IsActive)
		{
			const FName RowName = FName(*FString::FromInt(BG.Id));
			const FBackgroundData* Row = BackgroundDataTable->FindRow<FBackgroundData>(RowName, TEXT("Find BG By Id"));
			if (!Row) continue;
			SetCurrentBackground(Row->Image);
			OnCurrentBackgroundSetDelegate.Broadcast(GetCurrentBackground());
			break;
		}
	}
}


void UBackgroundManager::SetCurrentBackground(UTexture2D* NewBackground)
{
	CurrentBackground = NewBackground;
}


UTexture2D* UBackgroundManager::GetCurrentBackground() const
{
	return CurrentBackground;
}


void UBackgroundManager::SetUnlockedBackgrounds(const TArray<FSavedBackgroundsData>& Backgrounds)
{
	UnlockedBackgrounds = Backgrounds;
	OnBackgroundsLoadedDelegate.Broadcast();
}


TArray<FSavedBackgroundsData> UBackgroundManager::GetUnlockedBackgrounds() const
{
	return UnlockedBackgrounds;
}


void UBackgroundManager::AddUnlockedBackground(const FSavedBackgroundsData& Background)
{
	UE_LOG(LogTemp, Warning, TEXT("Id: %i"), Background.Id);
	UnlockedBackgrounds.Push(Background);
}
