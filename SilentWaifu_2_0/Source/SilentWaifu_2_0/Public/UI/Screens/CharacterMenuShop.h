
#pragma once

#include "CoreMinimal.h"
#include "UI/Screens/CharacterMenuBase.h"
#include "CharacterMenuShop.generated.h"


UCLASS()
class SILENTWAIFU_2_0_API UCharacterMenuShop : public UCharacterMenuBase
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	UFUNCTION()
	void UpdateShop();

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
	
	UPROPERTY(EditAnywhere)
	UDataTable* CharacterDataTable;
	
	UPROPERTY(EditAnywhere)
	UDataTable* RarityDataTable;
	
	int AmountOfSlots = 5;

	int MaxRandomNumber = 100;

	FTimespan UpdateTime;

	FTimerHandle TimerHandle;
};
