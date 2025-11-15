
#include "GameMode/Helpers/BackgroundManager.h"


void UBackgroundManager::Init(UDataTable* DataTable)
{
	BackgroundDataTable = DataTable;
	OnBackgroundsLoadedDelegate.AddDynamic(this, &UBackgroundManager::HandleSetBackground);
}


void UBackgroundManager::HandleSetBackground()
{
	if (!BackgroundDataTable) return;
	for (const auto& Bg : UnlockedBackgrounds)
	{
		if (Bg.IsActive)
		{
			const FName RowName = FName(*FString::FromInt(Bg.Id));
			const FBackgroundData* Row = BackgroundDataTable->FindRow<FBackgroundData>(RowName, TEXT("Find BG By Id"));
			if (!Row) continue;
			SetCurrentBackgroundImage(Row->Image);
			OnCurrentBackgroundSetDelegate.Broadcast(GetCurrentBackground());
			break;
		}
	}
}


void UBackgroundManager::SetCurrentBackgroundImage(UTexture2D* NewBackground)
{
	CurrentBackground = NewBackground;
	OnCurrentBackgroundSetDelegate.Broadcast(CurrentBackground);
}


void UBackgroundManager::SetCurrentBackgroundId(int Id)
{
	for (auto& Bg : UnlockedBackgrounds)
	{
		if (Bg.Id == Id) Bg.IsActive = true;
		else Bg.IsActive = false;
	}
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
	UnlockedBackgrounds.Add(Background);
}