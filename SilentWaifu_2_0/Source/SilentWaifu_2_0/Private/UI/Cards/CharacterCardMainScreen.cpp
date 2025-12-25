
#include "UI/Cards/CharacterCardMainScreen.h"
#include "Components/Button.h"
#include "DataTables/CharacterData.h"
#include "DataTables/CharacterRarities.h"
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
	SetAbilityImage();
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


void UCharacterCardMainScreen::SetAbilityImage()
{
	UTexture2D* AbilityImage = GetAbilityImage();
	FButtonStyle CustomStyle = Button_Ability->GetStyle();
	
	FSlateBrush NormalBrush = CustomStyle.Normal;
	FSlateBrush HoveredBrush = CustomStyle.Hovered;
	FSlateBrush PressedBrush = CustomStyle.Pressed;
	
	NormalBrush.SetResourceObject(AbilityImage);
	NormalBrush.DrawAs = ESlateBrushDrawType::Image;
	
	HoveredBrush.SetResourceObject(AbilityImage);
	HoveredBrush.DrawAs = ESlateBrushDrawType::Image;
	
	PressedBrush.SetResourceObject(AbilityImage);
	PressedBrush.DrawAs = ESlateBrushDrawType::Image;
	
	CustomStyle.SetNormal(NormalBrush);
	CustomStyle.SetHovered(HoveredBrush);
	CustomStyle.SetPressed(PressedBrush);
	Button_Ability->SetStyle(CustomStyle);
}


UTexture2D* UCharacterCardMainScreen::GetAbilityImage()
{
	if (!RarityDataTable) return nullptr;
	const FName CharacterRarityName = StaticEnum<ERarities>()->GetNameByValue(static_cast<int64>(GetCharacterData()->Rarity));
	const FCharacterRarities* Row = RarityDataTable->FindRow<FCharacterRarities>(CharacterRarityName, TEXT("Find ability image"));
	return Row ? Row->AbilityData.Icon : nullptr;
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
