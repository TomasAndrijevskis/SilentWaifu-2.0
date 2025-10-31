
#pragma once

#include "CoreMinimal.h"
#include "CharacterCardBase.h"
#include "DataTables/CharacterData.h"
#include "CharacterCardShop.generated.h"


class USilentWaifuGameInstance;
class UImage;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCardCreatedSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCharacterUnlockedSignature);
UCLASS()
class SILENTWAIFU_2_0_API UCharacterCardShop : public UCharacterCardBase
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;
	
	void CreateLimitIncreaseCard();

	FOnCardCreatedSignature OnCardCreatedDelegate;
	
	FOnCharacterUnlockedSignature OnCharacterUnlockedDelegate;
	
protected:

	virtual void SetImage(UTexture2D* NewImage) override;
	
	virtual void Action() override;

private:

	UPROPERTY(meta = (BindWidget))
	UImage* Image_CardImage;

	UPROPERTY(EditAnywhere)
	UTexture2D* Image_LimitIncreaseImage;

	UFUNCTION()
	void HandleState();

	UFUNCTION()
	void UnlockCharacter();

	UFUNCTION()
	void SetGameInstance();
	
	int GetCharacterPrice() const;

	UFUNCTION()
	void SetCharacterRow();
	
	const FCharacterData* CharacterRow;
	
	UPROPERTY()
	USilentWaifuGameInstance* GameInstance;

};
