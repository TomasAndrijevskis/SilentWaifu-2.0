
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UnlockCharacterButton.generated.h"


class ASilentWaifuGameMode;
class USilentWaifuGameInstance;
class ACharacterTemplate;
class UButton;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCharacterUnlockedSignature);

UCLASS()
class SILENTWAIFU_2_0_API UUnlockCharacterButton : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	FOnCharacterUnlockedSignature OnCharacterUnlockedDelegate;
	
private:

	UPROPERTY(meta = (BindWidget))
	UButton* Button_UnlockCharacter;
	
	UFUNCTION()
	void UnlockCharacter();

	void SetGameInstance();

	void SetGameMode();

	UFUNCTION()
	void UpdateCharacterUnlockStatus();
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<ACharacterTemplate> CharacterClass;

	UPROPERTY(EditAnywhere)
	int CharacterId;

	UPROPERTY(EditAnywhere)
	int Cost;
	
	UPROPERTY()
	USilentWaifuGameInstance* GameInstance;

	UPROPERTY()
	ASilentWaifuGameMode* GameMode;
};
