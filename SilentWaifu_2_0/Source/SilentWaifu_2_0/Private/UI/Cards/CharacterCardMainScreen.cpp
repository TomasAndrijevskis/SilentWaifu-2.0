
#include "UI/Cards/CharacterCardMainScreen.h"
#include "Components/Button.h"
#include "DataTables/CharacterData.h"
#include "GameMode/Helpers/CharactersManager.h"


void UCharacterCardMainScreen::Init()
{
	Super::Init();
	Button_Action->OnClicked.Clear();
	Button_Action->OnPressed.AddDynamic(this, &UCharacterCardMainScreen::EnablePressedTimer);
	Button_Action->OnReleased.AddDynamic(this, &UCharacterCardMainScreen::DisablePressedTimer);
	Button_Ability->OnClicked.AddUniqueDynamic(this, &UCharacterCardMainScreen::ActivateAbility);
	OnCardCreatedDelegate.AddUniqueDynamic(this, &UCharacterCardMainScreen::OnCardCreated);
}


void UCharacterCardMainScreen::OnCardCreated()
{
	SetImage(GetCharacterData()->Images.MainScreenImage);
}


void UCharacterCardMainScreen::SetImage(UTexture2D* NewImage)
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
	HoveredBrush.TintColor = FSlateColor(FLinearColor(0.65f, .4f, .4f, 1.f)); 
	
	// Apply Brushes
	CustomStyle.SetNormal(NormalBrush);
	CustomStyle.SetHovered(HoveredBrush);
	CustomStyle.SetPressed(HoveredBrush);
	
	Button_Action->SetStyle(CustomStyle);
}


void UCharacterCardMainScreen::ActivateAbility()
{
	UE_LOG(LogTemp, Warning, TEXT("Activating Ability"));
}


void UCharacterCardMainScreen::EnablePressedTimer()
{
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UCharacterCardMainScreen::Action, 1, false);
}


void UCharacterCardMainScreen::DisablePressedTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}


void UCharacterCardMainScreen::Action()
{
	if (!CharactersManager) return;
	CharactersManager->RemoveCharacter(CharacterId);
}
