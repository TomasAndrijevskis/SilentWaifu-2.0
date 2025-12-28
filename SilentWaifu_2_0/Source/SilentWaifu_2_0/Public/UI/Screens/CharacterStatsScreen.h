
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DataTables/CharacterData.h"
#include "CharacterStatsScreen.generated.h"


class UWidgetReferenceDataAsset;
class UHorizontalBoxSlot;
class UScaleBox;
class UTextBlock;
class UButton;
class UHorizontalBox;

UCLASS()
class SILENTWAIFU_2_0_API UCharacterStatsScreen : public UUserWidget
{
	GENERATED_BODY()

public:

	void Init(FCharacterData* CharacterData);

		
protected:

	UPROPERTY(EditAnywhere)
	UWidgetReferenceDataAsset* WidgetReferences;
	
private:

	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* HorizontalBox_Content;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_AbilityDescription;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_CoolDown;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Close;
	
	void CreateSlots(int MaxLevel);

	void FillSlots();

	void SetAbilityInfo();
	
	UScaleBox* CreateLevelStatLine(int Level);
	
	UTextBlock* CreateTextBlock(const FString& Text, int FontSize);

	void SetAlignment(UHorizontalBoxSlot* HBSlot, const EHorizontalAlignment& HAlign,  const EVerticalAlignment& VAlign) const;

	UFUNCTION()
	void RemoveStatsScreen();

	UPROPERTY(EditAnywhere)
	UDataTable* RarityDataTable;
	
	FCharacterData* CharacterRow;

	int AmountOfColumns = 2;

	int AmountOfRows;
};
