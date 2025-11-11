
#include "UI/Screens/BackgroundMenu.h"
#include "Components/WrapBox.h"
#include "DataTables/BackgroundData.h"
#include "UI/WidgetReferenceDataAsset.h"
#include "UI/Cards/BackgroundCard.h"


void UBackgroundMenu::NativeConstruct()
{
	Super::NativeConstruct();
	CreateCards();
}


void UBackgroundMenu::CreateCards()
{
	TArray<FBackgroundData*> BackgroundData = GetBackgroundData();
	for (const auto& Data : BackgroundData)
	{
		WrapBox->AddChild(CreateBackgroundCard(Data->Image));
	}
}


UBackgroundCard* UBackgroundMenu::CreateBackgroundCard(UTexture2D* Image)
{
	if (!WidgetReferences || !WidgetReferences->BackgroundCardClass) return nullptr;
	UBackgroundCard* BgCard = Cast<UBackgroundCard>(CreateWidget(GetWorld(), WidgetReferences->BackgroundCardClass));
	if (!BgCard) return nullptr;
	BgCard->CreateCard(Image);
	return BgCard;
}


TArray<FBackgroundData*> UBackgroundMenu::GetBackgroundData() const
{
	if (!BackgroundsDataTable) return {};
	TArray<FBackgroundData*> Data {};
	BackgroundsDataTable->GetAllRows(TEXT("Get All Backgrounds"), Data);
	if (Data.Num() == 0) return {};
	return Data;
}
