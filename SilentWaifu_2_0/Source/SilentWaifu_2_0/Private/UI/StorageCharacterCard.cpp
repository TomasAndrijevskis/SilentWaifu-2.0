
#include "UI/StorageCharacterCard.h"
#include "Components/Button.h"
#include "DataTables/CharacterData.h"


void UStorageCharacterCard::SetImage(UTexture2D* NewImage)
{
	if (!NewImage)
	{
		return;
	}
	FButtonStyle CustomStyle;

	// Normal Brush (Image)
	FSlateBrush NormalBrush;
	NormalBrush.SetResourceObject(NewImage);
	NormalBrush.DrawAs = ESlateBrushDrawType::Image;
	NormalBrush.Tiling = ESlateBrushTileType::NoTile;
	NormalBrush.ImageSize = ImageSize;
	
	// Hovered Brush
	FSlateBrush HoveredBrush;
	HoveredBrush.SetResourceObject(NewImage);
	HoveredBrush.DrawAs = ESlateBrushDrawType::RoundedBox;
	HoveredBrush.Tiling = ESlateBrushTileType::NoTile;
	HoveredBrush.ImageSize = ImageSize;
	
	// Disabled Brush
	FSlateBrush DisabledBrush;
	DisabledBrush.SetResourceObject(NewImage);
	DisabledBrush.DrawAs = ESlateBrushDrawType::Image;
	DisabledBrush.Tiling = ESlateBrushTileType::NoTile;
	DisabledBrush.ImageSize = ImageSize;
	DisabledBrush.TintColor = FSlateColor(FLinearColor(1.f, 1.f, 1.f, 0.3f)); 
	
	// Apply Brushes
	CustomStyle.SetNormal(NormalBrush);
	CustomStyle.SetHovered(HoveredBrush);
	CustomStyle.SetDisabled(DisabledBrush);
	CustomStyle.SetPressed(HoveredBrush);
	
	Button_Character->SetStyle(CustomStyle);
	
}


void UStorageCharacterCard::CreateCard(const int Id)
{
	UE_LOG(LogTemp, Warning, TEXT("UStorageCharacterCard::CreateCard"));
	if (!CharacterDataTable) return;
	FName RowName = FName(*FString::FromInt(Id));
	FCharacterData* CharacterRow = CharacterDataTable->FindRow<FCharacterData>(RowName, TEXT("Find Character By Id"));
	if (!CharacterRow)	return;
	SetImage(CharacterRow->Image);
}
