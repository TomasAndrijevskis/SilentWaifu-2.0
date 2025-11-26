
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DataTables/CharacterData.h"
#include "CharacterStatsScreen.generated.h"


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

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Close;

	void Init(FCharacterData* CharacterData);

private:

	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* HorizontalBox_Content;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_AbilityDescription;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_CoolDown;
	
	void CreateSlots(int MaxLevel);

	void FillSlots();

	UScaleBox* CreateLevelStatLine(int Level);
	
	UTextBlock* CreateTextBlock(const FString& Text, int FontSize);

	void SetAlignment(UHorizontalBoxSlot* HBSlot, const EHorizontalAlignment& HAlign,  const EVerticalAlignment& VAlign) const;
	
	FCharacterData* CharacterRow;

	int AmountOfColumns = 2;

	int AmountOfRows;
};
