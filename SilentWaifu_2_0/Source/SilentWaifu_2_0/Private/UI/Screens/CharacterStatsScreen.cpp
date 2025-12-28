
#include "UI/Screens/CharacterStatsScreen.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/ScaleBox.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "DataTables/CharacterRarities.h"
#include "UI/WidgetReferenceDataAsset.h"


void UCharacterStatsScreen::Init(FCharacterData* CharacterData)
{
	if (!CharacterData) return;
	CharacterRow = CharacterData;
	CreateSlots(CharacterRow->Numbers.MaxLevel);
	SetAbilityInfo();
	Button_Close->OnClicked.AddDynamic(this, &UCharacterStatsScreen::RemoveStatsScreen);
}


void UCharacterStatsScreen::CreateSlots(int MaxLevel)
{
	AmountOfRows = MaxLevel / AmountOfColumns;
	for (int i = 0 ; i < AmountOfColumns; i++)
	{
		UVerticalBox* VB = NewObject<UVerticalBox>(this);
		if (!VB) return;
		UHorizontalBoxSlot* HBSlot = Cast<UHorizontalBoxSlot>(HorizontalBox_Content->AddChild(VB));
		if (!HBSlot) return;
		HBSlot->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
		HBSlot->SetHorizontalAlignment(HAlign_Center);
		HBSlot->SetVerticalAlignment(VAlign_Center);
	}
	FillSlots();
}


void UCharacterStatsScreen::FillSlots()
{
	int Level = 1;
	for (const auto& VBSlot : HorizontalBox_Content->GetAllChildren())
	{
		for (int i = 0 ; i < AmountOfRows; i++)
		{
			Cast<UVerticalBox>(VBSlot)->AddChild(CreateLevelStatLine(Level));
			Level++;
		}
	}
}


void UCharacterStatsScreen::SetAbilityInfo()
{
	if (!RarityDataTable || !CharacterRow) return;
	const FName CharacterRarityName = StaticEnum<ERarities>()->GetNameByValue(static_cast<int64>(CharacterRow->Rarity));
	FCharacterRarities* RarityRow = RarityDataTable->FindRow<FCharacterRarities>(CharacterRarityName, TEXT("Find rarity row"));
	if (!RarityRow) return;

	Text_AbilityDescription->SetText(FText::FromString(RarityRow->AbilityData.Description));
	Text_CoolDown->SetText(FText::AsNumber(RarityRow->AbilityData.Cooldown));
}


UScaleBox* UCharacterStatsScreen::CreateLevelStatLine(int Level)
{
	UScaleBox* ScaleBox = NewObject<UScaleBox>(this);
	UHorizontalBox* HBox = NewObject<UHorizontalBox>(this);
	if (!ScaleBox || !HBox) return nullptr;
	ScaleBox->AddChild(HBox);
	
	FString LevelText = "Level "+ FString::FromInt(Level) +": ";
	UHorizontalBoxSlot* HBSlot_LevelText = Cast<UHorizontalBoxSlot>(HBox->AddChild(CreateTextBlock(LevelText, 30)));
	SetAlignment(HBSlot_LevelText, HAlign_Left, VAlign_Center);

	FString CoinsText = FString::FromInt(CharacterRow->Numbers.CoinsPerLevel[Level-1]);
	UHorizontalBoxSlot* HBSlot_LevelValue = Cast<UHorizontalBoxSlot>(HBox->AddChild(CreateTextBlock(CoinsText, 40)));
	SetAlignment(HBSlot_LevelValue, HAlign_Fill, VAlign_Fill);
	
	return ScaleBox;
}


UTextBlock* UCharacterStatsScreen::CreateTextBlock(const FString& Text, int FontSize)
{
	UTextBlock* TextBlock = NewObject<UTextBlock>(this);
	if (!TextBlock) return nullptr;
	TextBlock->SetText(FText::FromString(Text));
	FSlateFontInfo FontText = TextBlock->GetFont();
	FontText.Size = FontSize;
	TextBlock->SetFont(FontText);
	return TextBlock;
}


void UCharacterStatsScreen::SetAlignment(UHorizontalBoxSlot* HBSlot, const EHorizontalAlignment& HAlign, const EVerticalAlignment& VAlign) const
{
	if (!HBSlot) return;
	HBSlot->SetHorizontalAlignment(HAlign);
	HBSlot->SetVerticalAlignment(VAlign);
}


void UCharacterStatsScreen::RemoveStatsScreen()
{
	if (!WidgetReferences || !WidgetReferences->CharacterStatsScreenRef) return;
	WidgetReferences->CharacterStatsScreenRef->RemoveFromParent();
	WidgetReferences->CharacterStatsScreenRef = nullptr;
}

