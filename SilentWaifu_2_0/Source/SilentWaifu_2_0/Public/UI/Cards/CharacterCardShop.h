
#pragma once

#include "CoreMinimal.h"
#include "CharacterCard.h"
#include "DataTables/CharacterData.h"
#include "CharacterCardShop.generated.h"


class UTextBlock;
class USilentWaifuGameInstance;
class UImage;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCharacterUnlockedSignature);
UCLASS()
class SILENTWAIFU_2_0_API UCharacterCardShop : public UCharacterCard
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;
	
	FOnCharacterUnlockedSignature OnCharacterUnlockedDelegate;
	
protected:

	virtual void SetImage(UTexture2D* NewImage) override;
	
	virtual void Action() override;

private:

	UPROPERTY(meta = (BindWidget))
	UButton* Button_CharacterImage;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_Price;
	
	UFUNCTION()
	void HandleState();

	UFUNCTION()
	void UnlockCharacter();

	UFUNCTION()
	void SetGameInstance();
	
	int GetCharacterPrice() const;

	UFUNCTION()
	void SetCharacterRow();

	UFUNCTION()
	void SetPriceText();
	
	const FCharacterData* CharacterRow;
	
	UPROPERTY()
	USilentWaifuGameInstance* GameInstance;

};
