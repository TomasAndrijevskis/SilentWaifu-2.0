
#include "UI/Screens/Guide.h"
#include "Components/Button.h"
#include "Components/Image.h"


void UGuide::NativeConstruct()
{
	Super::NativeConstruct();
	Button_Next->OnClicked.AddUniqueDynamic(this, &UGuide::NextImage);
	Button_Previous->OnClicked.AddUniqueDynamic(this, &UGuide::PreviousImage);
	Button_Skip->OnClicked.AddUniqueDynamic(this, &UGuide::RemoveGuide);
	SetGuideImage();
	HandleButtons();
}


void UGuide::RebindActions(bool IsLastImage)
{
	if (IsLastImage)
	{
		Button_Next->OnClicked.Clear();
		Button_Next->OnClicked.AddUniqueDynamic(this, &UGuide::RemoveGuide);
	}
	else
	{
		Button_Next->OnClicked.Clear();
		Button_Next->OnClicked.AddUniqueDynamic(this, &UGuide::NextImage);
	}
}


void UGuide::NextImage()
{
	if (GuideImages.Num() - 1 > CurrentGuideIndex)
	{
		CurrentGuideIndex++;
		SetGuideImage();
		HandleButtons();
	}
}

void UGuide::PreviousImage()
{
	if (CurrentGuideIndex == GuideImages.Num() - 1) RebindActions(false);
	if (CurrentGuideIndex > 0)
	{
		CurrentGuideIndex--;
		SetGuideImage();
		HandleButtons();
	}
}


void UGuide::SetGuideImage()
{
	Image_Guide->SetBrushFromTexture(GuideImages[CurrentGuideIndex]);
}


void UGuide::HandleButtons()
{
	if (CurrentGuideIndex == 0) Button_Previous->SetVisibility(ESlateVisibility::Hidden);
	else if (CurrentGuideIndex == GuideImages.Num() - 1) RebindActions(true);
	else
	{
		Button_Previous->SetVisibility(ESlateVisibility::Visible);
		Button_Next->SetVisibility(ESlateVisibility::Visible);
	}
}


void UGuide::RemoveGuide()
{
	this->RemoveFromParent();
}
