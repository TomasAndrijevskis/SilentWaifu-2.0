
#include "UI/Screens/BackgroundMenu.h"
#include "Components/Button.h"
#include "Components/WrapBox.h"
#include "DataTables/BackgroundData.h"
#include "UI/WidgetReferenceDataAsset.h"
#include "UI/Cards/BackgroundCard.h"
#include "UI/Screens/MainScreen.h"


void UBackgroundMenu::NativeConstruct()
{
	Super::NativeConstruct();
	CreateCards();
	Button_Close->OnClicked.AddDynamic(this, &UBackgroundMenu::RemoveMenu);
	if (!WidgetReferences || !WidgetReferences->MainScreenRef) return;
	WidgetReferences->MainScreenRef->OnBackgroundSetDelegate.AddDynamic(this, &UBackgroundMenu::RemoveMenu);
}


void UBackgroundMenu::CreateCards()
{
	TArray<FBackgroundData*> BackgroundData = GetBackgroundData();
	for (const auto& Data : BackgroundData)
	{
		WrapBox->AddChild(CreateBackgroundCard(Data->Image, Data->ID, Data->Price));
	}
}


UBackgroundCard* UBackgroundMenu::CreateBackgroundCard(UTexture2D* Image, int Id, int Price) const
{
	if (!WidgetReferences || !WidgetReferences->BackgroundCardClass) return nullptr;
	UBackgroundCard* BgCard = Cast<UBackgroundCard>(CreateWidget(GetWorld(), WidgetReferences->BackgroundCardClass));
	if (!BgCard) return nullptr;
	BgCard->CreateCard(Image, Id, Price);
	return BgCard;
}


TArray<FBackgroundData*> UBackgroundMenu::GetBackgroundData() const
{
	if (!BackgroundsDataTable) return {};
	TArray<FBackgroundData*> Data;
	BackgroundsDataTable->GetAllRows(TEXT("Get All Backgrounds"), Data);
	return Data;
}


void UBackgroundMenu::RemoveMenu()
{
	if (!WidgetReferences || !WidgetReferences->BackgroundMenuRef) return;
	WidgetReferences->BackgroundMenuRef->RemoveFromParent();
	WidgetReferences->BackgroundMenuRef = nullptr;
}