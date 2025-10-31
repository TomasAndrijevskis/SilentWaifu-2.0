
#include "UI/Cards/CharacterCardShop.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "GameMode/SilentWaifuGameMode.h"


void UCharacterCardShop::CreateLimitIncreaseCard()
{
	UE_LOG(LogTemp, Warning, TEXT("UCharacterCardShop::CreateLimitIncreaseCard"));
	SetImage(Image_LimitIncreaseImage);
}


void UCharacterCardShop::SetImage(UTexture2D* NewImage)
{
	if (!NewImage) return;
	Image_CardImage->SetDesiredSizeOverride(ImageSize);
	Image_CardImage->SetBrushFromTexture(NewImage);
}


void UCharacterCardShop::Action()
{
	
}


void UCharacterCardShop::HandleCardState()
{
	Button_Character->SetIsEnabled(GameMode->GetAvailableCharacters().Contains(CharacterId));
}
