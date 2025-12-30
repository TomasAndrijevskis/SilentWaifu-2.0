
#include "UI/Cards/CharacterCardMainScreen.h"
#include "Character/CharacterTemplate.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"
#include "DataTables/CharacterData.h"
#include "DataTables/CharacterRarities.h"
#include "GameMode/Helpers/CharactersManager.h"
#include "UI/CharacterAbilityCooldownPanel.h"


void UCharacterCardMainScreen::Init()
{
	Super::Init();
	Button_Action->OnClicked.Clear();
	Button_Action->OnPressed.AddDynamic(this, &UCharacterCardMainScreen::EnablePressedTimer);
	Button_Action->OnReleased.AddDynamic(this, &UCharacterCardMainScreen::DisablePressedTimer);
	Button_Action->OnClicked.AddUniqueDynamic(this, &UCharacterCardMainScreen::CreateAbilityCooldownPanel);
	Button_Ability->OnClicked.AddUniqueDynamic(this, &UCharacterCardMainScreen::ActivateAbility);
	OnCardCreatedDelegate.AddUniqueDynamic(this, &UCharacterCardMainScreen::OnCardCreated);
	OnCardCreatedDelegate.AddUniqueDynamic(this, &UCharacterCardMainScreen::HandleAbilityButtonState);
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


void UCharacterCardMainScreen::ActivateAbility()
{
	FSavedCharactersData* Data = GetCharactersSavedData();
	if (!Data || !Data->SpawnedCharacter) return;
	Data->SpawnedCharacter->ActivateAbility();
	Data->AbilityData.UsageTime = FDateTime::Now();
	Data->AbilityData.WasAbilityUsed = true;
	HandleAbilityButtonState();
}


void UCharacterCardMainScreen::HandleAbilityButtonState()
{
	bool bCanUseAbility = CanUseAbility();
	Button_Ability->SetIsEnabled(bCanUseAbility);
	FSavedCharactersData* Data = GetCharactersSavedData();
	if (!Data) return;
	if (bCanUseAbility) Data->AbilityData.WasAbilityUsed = false;
	else SetCooldownTimer();
}


void UCharacterCardMainScreen::SetCooldownTimer()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(CooldownTimerHandle)) return;
	float CooldownTimeLeft = (GetCooldownEndTime() - FDateTime::Now()).GetTotalSeconds();
	if (CooldownTimeLeft <= 0.f)
	{
		HandleAbilityButtonState();
		return;
	}
	GetWorld()->GetTimerManager().SetTimer(CooldownTimerHandle, this, &UCharacterCardMainScreen::OnCooldownFinished, .1f, false, CooldownTimeLeft);
}


void UCharacterCardMainScreen::OnCooldownFinished()
{
	GetWorld()->GetTimerManager().ClearTimer(CooldownTimerHandle);
	HandleAbilityButtonState();
}


FDateTime UCharacterCardMainScreen::GetCooldownEndTime()
{
	const FSavedCharactersData* Data = GetCharactersSavedData();
	const FCharacterRarities* RarityRow = GetCharacterRarity();
	if (!Data || !RarityRow) return 0;
	const int CooldownHours = RarityRow->AbilityData.Cooldown;
	return Data->AbilityData.UsageTime + FTimespan::FromHours(CooldownHours);
}


void UCharacterCardMainScreen::CreateAbilityCooldownPanel()
{
	if (!CharacterAbilityCooldownPanelClass) return;
	CharacterAbilityCooldownPanelRef = Cast<UCharacterAbilityCooldownPanel>(CreateWidget(GetWorld(), CharacterAbilityCooldownPanelClass));
	if (!CharacterAbilityCooldownPanelRef) return;
	CharacterAbilityCooldownPanelRef->Init(GetCooldownEndTime());
	CharacterAbilityCooldownPanelRef->OnCooldownEndedDelegate.AddUniqueDynamic(this, &UCharacterCardMainScreen::RemoveAbilityCooldownPanel);
	HorizontalBox_CooldownTimer->AddChild(CharacterAbilityCooldownPanelRef);
	RebindActions(true);
}


void UCharacterCardMainScreen::RemoveAbilityCooldownPanel()
{
	if (!CharacterAbilityCooldownPanelRef) return;
	HorizontalBox_CooldownTimer->RemoveChildAt(0);
	CharacterAbilityCooldownPanelRef->RemoveFromParent();
	CharacterAbilityCooldownPanelRef = nullptr;
	RebindActions(false);
}


void UCharacterCardMainScreen::RebindActions(bool IsCooldownPanelCreated)
{
	Button_Action->OnClicked.Clear();
	if (!IsCooldownPanelCreated) Button_Action->OnClicked.AddUniqueDynamic(this, &UCharacterCardMainScreen::CreateAbilityCooldownPanel);
	else Button_Action->OnClicked.AddUniqueDynamic(this, &UCharacterCardMainScreen::RemoveAbilityCooldownPanel);
}


void UCharacterCardMainScreen::EnablePressedTimer()
{
	GetWorld()->GetTimerManager().SetTimer(PressedTimerHandle, this, &UCharacterCardMainScreen::Action, 1, false);
}


void UCharacterCardMainScreen::DisablePressedTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(PressedTimerHandle);
}


void UCharacterCardMainScreen::Action()
{
	if (!CharactersManager) return;
	CharactersManager->RemoveCharacter(CharacterId);
}


FSavedCharactersData* UCharacterCardMainScreen::GetCharactersSavedData() const
{
	return CharactersManager ? CharactersManager->GetAvailableCharacters().Find(CharacterId) : nullptr;
}


FCharacterRarities* UCharacterCardMainScreen::GetCharacterRarity()
{
	if (!RarityDataTable) return nullptr;
	const FName CharacterRarityName = StaticEnum<ERarities>()->GetNameByValue(static_cast<int64>(GetCharacterData()->Rarity));
	FCharacterRarities* RarityRow = RarityDataTable->FindRow<FCharacterRarities>(CharacterRarityName, TEXT("Find ability image"));
	return RarityRow;
}


bool UCharacterCardMainScreen::CanUseAbility()
{
	FSavedCharactersData* Data = GetCharactersSavedData();
	FCharacterRarities* RarityRow = GetCharacterRarity();
	if (!Data || !RarityRow) return false;
	if (!Data->AbilityData.WasAbilityUsed) return true;
	int CooldownHours = RarityRow->AbilityData.Cooldown;
	FDateTime CooldownEndTime = Data->AbilityData.UsageTime + FTimespan::FromHours(CooldownHours);
	return FDateTime::Now() >= CooldownEndTime;
}


UTexture2D* UCharacterCardMainScreen::GetAbilityImage()
{
	FCharacterRarities* RarityRow = GetCharacterRarity();
	return RarityRow ? RarityRow->AbilityData.Icon : nullptr;
}
