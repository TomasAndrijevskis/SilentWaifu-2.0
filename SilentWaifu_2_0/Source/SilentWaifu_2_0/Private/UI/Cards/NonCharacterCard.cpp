
#include "UI/Cards/NonCharacterCard.h"


void UNonCharacterCard::CreateCard()
{
	SetImage(Image_LimitIncreaseImage);
	OnCardCreatedDelegate.Broadcast();
}
