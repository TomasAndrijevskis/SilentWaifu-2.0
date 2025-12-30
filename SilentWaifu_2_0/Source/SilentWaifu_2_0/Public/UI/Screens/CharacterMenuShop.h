
#pragma once

#include "CoreMinimal.h"
#include "UI/Screens/CharacterMenuBase.h"
#include "CharacterMenuShop.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnShopNeedUpdateSignature);
UCLASS()
class SILENTWAIFU_2_0_API UCharacterMenuShop : public UCharacterMenuBase
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	UFUNCTION()
	void UpdateShop();

	FOnShopNeedUpdateSignature OnShopNeedUpdateDelegate;
	
protected:

	virtual void CreateCharacterMenu() override;
	
	virtual void RemoveCharacterMenu() override;
	
private:

	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* HorizontalBox_Shop;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_UpdateShop;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_RemainingTime;
	
	TArray<int>& GetRandomCharacters(TArray<int>& OutCharacters);

	int GetCharacterRarity();

	int GetCharacter();
	
	void CreateShop(TArray<int> Characters);

	void CreateTimeCountdown();

	void CheckLiveShopUpdate(const FString& TimeLeft);

	void CheckUpdateAfterShutdown();
	
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
