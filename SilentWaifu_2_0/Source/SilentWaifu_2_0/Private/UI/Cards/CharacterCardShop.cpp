
#include "UI/Cards/CharacterCardShop.h"
#include "Components/Image.h"


void UCharacterCardShop::CreateLimitIncreaseCard()
{
	SetImage(Image_LimitIncreaseImage);
}


void UCharacterCardShop::SetImage(UTexture2D* NewImage)
{
	if (!NewImage)
	{
		return;
	}
	Image_CardImage->SetDesiredSizeOverride(ImageSize);
	Image_CardImage->SetBrushFromTexture(NewImage);
}


void UCharacterCardShop::Action()
{
	
}
