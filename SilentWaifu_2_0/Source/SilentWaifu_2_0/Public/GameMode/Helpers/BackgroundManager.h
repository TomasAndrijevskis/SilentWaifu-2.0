
#pragma once

#include "CoreMinimal.h"
#include "DataTables/BackgroundData.h"
#include "SaveGame/SavedBackgroundsData.h"
#include "BackgroundManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBackgroundsLoadedSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCurrentBackgroundSetSignature, UTexture2D*, Background);

UCLASS()
class SILENTWAIFU_2_0_API UBackgroundManager : public UObject
{
	GENERATED_BODY()

public:

	void Init(UDataTable* DataTable);
	
	void SetCurrentBackgroundImage(UTexture2D* NewBackground);

	void SetCurrentBackgroundId(int Id);
	
	UFUNCTION()
	UTexture2D* GetCurrentBackground() const;
	
	void SetUnlockedBackgrounds(const TArray<FSavedBackgroundsData>& Backgrounds);

	TArray<FSavedBackgroundsData> GetUnlockedBackgrounds() const;

	void AddUnlockedBackground(const FSavedBackgroundsData& Background);
	
	FOnBackgroundsLoadedSignature OnBackgroundsLoadedDelegate;

	FOnCurrentBackgroundSetSignature OnCurrentBackgroundSetDelegate;
	
private:

	UFUNCTION()
	void HandleSetBackground();
	
	UPROPERTY()
	UTexture2D* CurrentBackground;

	UPROPERTY()
	UDataTable* BackgroundDataTable;
	
	TArray<FSavedBackgroundsData> UnlockedBackgrounds;
};
