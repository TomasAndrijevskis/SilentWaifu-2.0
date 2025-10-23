
#include "UI/CharacterCardChoose.h"
#include "Components/Button.h"
#include "GameMode/SilentWaifuGameMode.h"


void UCharacterCardChoose::NativeConstruct()
{
	Super::NativeConstruct();
	Button_Character->OnClicked.AddUniqueDynamic(this,&UCharacterCardChoose::HandleCardState);
}


void UCharacterCardChoose::SetImage(UTexture2D* NewImage)
{
	if (!NewImage) return;
	
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
	HandleCardState();
}


void UCharacterCardChoose::HandleCardState()
{
	FSavedCharactersData* Data = GameMode->GetAvailableCharacters().Find(CharacterId);
	Button_Character->SetIsEnabled(!Data->bIsOnScreen);
}


void UCharacterCardChoose::Action()
{
	GameMode->SpawnCharacter(CharacterId);
}


