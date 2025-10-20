
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UnlockCharacterButton.generated.h"


class USilentWaifuGameInstance;
class ACharacterTemplate;
class UButton;

UCLASS()
class SILENTWAIFU_2_0_API UUnlockCharacterButton : public UUserWidget
{
	GENERATED_BODY()

public:

	void NativeConstruct() override;


private:

	UPROPERTY(meta = (BindWidget))
	UButton* Button_UnlockCharacter;
	
	UFUNCTION()
	void UnlockCharacter();

	void SetGameInstance();
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<ACharacterTemplate> CharacterClass;

	UPROPERTY(EditAnywhere)
	int CharacterId;
	
	UPROPERTY()
	USilentWaifuGameInstance* GameInstance;
};
