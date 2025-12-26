
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
	FButtonStyle Style;
	ApplyCardBrushStyle(Style.Normal, NewImage);
	ApplyCardBrushStyle(Style.Hovered, NewImage);
	Style.Hovered.TintColor = FSlateColor(FLinearColor(0.65f, .4f, .4f, 1.f)); 
	ApplyCardBrushStyle(Style.Pressed, NewImage);
	Style.Pressed.TintColor = FSlateColor(FLinearColor(0.65f, .2f, .2f, 1.f)); 
	Button_Action->SetStyle(Style);
}


void UCharacterCardMainScreen::ApplyCardBrushStyle(FSlateBrush& BrushStyle, UTexture2D* Image)
{
	BrushStyle.SetResourceObject(Image);
	BrushStyle.DrawAs = ESlateBrushDrawType::Image;
	BrushStyle.Tiling = ESlateBrushTileType::NoTile;
	BrushStyle.ImageSize = ImageSize;
}


void UCharacterCardMainScreen::SetAbilityImage()
{
	UTexture2D* AbilityImage = GetAbilityImage();
	if (!AbilityImage) return;
	FButtonStyle Style = Button_Ability->GetStyle();
	ApplyAbilityBrushStyle(Style.Normal, AbilityImage);
	ApplyAbilityBrushStyle(Style.Hovered, AbilityImage);
	ApplyAbilityBrushStyle(Style.Pressed, AbilityImage);
	Button_Ability->SetStyle(Style);
}


void UCharacterCardMainScreen::ApplyAbilityBrushStyle(FSlateBrush& BrushStyle, UTexture2D* AbilityImage) const
{
	BrushStyle.SetResourceObject(AbilityImage);
	BrushStyle.DrawAs = ESlateBrushDrawType::Image;
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
