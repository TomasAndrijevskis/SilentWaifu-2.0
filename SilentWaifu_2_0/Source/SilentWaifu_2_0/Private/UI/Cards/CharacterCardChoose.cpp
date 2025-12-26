
#include "UI/Cards/CharacterCardChoose.h"
#include "Components/Button.h"
#include "GameMode/Helpers/CharactersManager.h"


void UCharacterCardChoose::Init()
{
	Super::Init();
	Button_Action->OnClicked.AddUniqueDynamic(this,&UCharacterCardChoose::HandleCardState);
}


void UCharacterCardChoose::SetImage(UTexture2D* NewImage)
{
	if (!NewImage) return;
	FButtonStyle Style;
	ApplyCardBrushStyle(Style.Normal, NewImage);
	ApplyCardBrushStyle(Style.Hovered, NewImage);
	Style.Hovered.TintColor = FSlateColor(FLinearColor(1.f, 1.f, 1.f, 0.8f)); 
	ApplyCardBrushStyle(Style.Pressed, NewImage);
	Style.Pressed.TintColor = FSlateColor(FLinearColor(1.f, 1.f, 1.f, 0.5f));
	ApplyCardBrushStyle(Style.Disabled, NewImage);
	Style.Disabled.TintColor = FSlateColor(FLinearColor(1.f, 1.f, 1.f, 0.2f));
	Button_Action->SetStyle(Style);
	HandleCardState();
}


void UCharacterCardChoose::ApplyCardBrushStyle(FSlateBrush& BrushStyle, UTexture2D* Image)
{
	BrushStyle.SetResourceObject(Image);
	BrushStyle.DrawAs = ESlateBrushDrawType::Image;
	BrushStyle.Tiling = ESlateBrushTileType::NoTile;
	BrushStyle.ImageSize = ImageSize;
}


void UCharacterCardChoose::HandleCardState()
{
	if (!CharactersManager) return;
	FSavedCharactersData* Data = CharactersManager->GetAvailableCharacters().Find(CharacterId);
	Button_Action->SetIsEnabled(!Data->bIsOnScreen);
}


void UCharacterCardChoose::Action()
{
	if (!CharactersManager) return;
	CharactersManager->SpawnCharacter(CharacterId);
}


