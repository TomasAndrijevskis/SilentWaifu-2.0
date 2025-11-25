
#include "UI/Screens/CharacterStoryLine.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"


void UCharacterStoryLine::Init(UTexture2D* Image, const FString& Name, const FString& Story)
{
	if (!Image) return;
	Image_Character->SetBrushFromTexture(Image);
	Text_CharacterName->SetText(FText::FromString(Name));
	Text_StoryLine->SetText(FText::FromString(Story));
}
