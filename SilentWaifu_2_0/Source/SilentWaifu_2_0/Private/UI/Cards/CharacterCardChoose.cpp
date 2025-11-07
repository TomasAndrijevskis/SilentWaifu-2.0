
#include "UI/Cards/CharacterCardChoose.h"
#include "Components/Button.h"
#include "GameMode/SilentWaifuGameMode.h"
#include "GameMode/Helpers/CharactersManager.h"


void UCharacterCardChoose::NativeConstruct()
{
	Super::NativeConstruct();
	Button_Action->OnClicked.AddUniqueDynamic(this,&UCharacterCardChoose::HandleCardState);
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
	HoveredBrush.DrawAs = ESlateBrushDrawType::Image;
	HoveredBrush.Tiling = ESlateBrushTileType::NoTile;
	HoveredBrush.ImageSize = ImageSize;
	HoveredBrush.TintColor = FSlateColor(FLinearColor(1.f, 1.f, 1.f, 0.7f)); 
	
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
	
	Button_Action->SetStyle(CustomStyle);
	HandleCardState();
}


void UCharacterCardChoose::HandleCardState()
{
	if (!GameMode) return;
	FSavedCharactersData* Data = GameMode->CharactersManager->GetAvailableCharacters().Find(CharacterId);
	Button_Action->SetIsEnabled(!Data->bIsOnScreen);
}


void UCharacterCardChoose::Action()
{
	if (!GameMode) return;
	GameMode->CharactersManager->SpawnCharacter(CharacterId);
}


