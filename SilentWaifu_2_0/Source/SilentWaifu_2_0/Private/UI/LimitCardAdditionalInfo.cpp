
#include "UI/LimitCardAdditionalInfo.h"
#include "Components/TextBlock.h"


void ULimitCardAdditionalInfo::SetText(int Amount)
{
	Text_Amount->SetText(FText::FromString(FString::FromInt(Amount)));
}
