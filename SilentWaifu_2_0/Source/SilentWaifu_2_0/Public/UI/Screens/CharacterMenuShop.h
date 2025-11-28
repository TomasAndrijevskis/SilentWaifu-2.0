
#pragma once

#include "CoreMinimal.h"
#include "UI/Screens/CharacterMenuBase.h"
#include "CharacterMenuShop.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnShopUpdatedSignature);
UCLASS()
class SILENTWAIFU_2_0_API UCharacterMenuShop : public UCharacterMenuBase
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	UFUNCTION()
	void UpdateShop();

	FOnShopUpdatedSignature OnShopUpdatedDelegate;
	
protected:

	virtual void CreateCharacterMenu() override;
	
	virtual void RemoveCharacterMenu() override;
	
private:

	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* HorizontalBox_Shop;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_UpdateShop;//testing

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_RemainingTime;
	
	TArray<int>& GetRandomCharacters(TArray<int>& OutCharacters);

	int GetCharacterRarity();

	int GetCharacter();
	
	void CreateShop(TArray<int> Characters);

	void CreateTimeCountdown();

	void CheckShopUpdate(const FString& TimeLeft);

	void CheckLastTime();
	
	UPROPERTY(EditAnywhere)
	UDataTable* CharacterDataTable;
	
	UPROPERTY(EditAnywhere)
	UDataTable* RarityDataTable;
	
	int AmountOfSlots = 5;

	int MaxRandomNumber = 100;

	FTimespan UpdateTime;

	FTimerHandle TimerHandle;

	bool CanUpdateShop = false;
};
