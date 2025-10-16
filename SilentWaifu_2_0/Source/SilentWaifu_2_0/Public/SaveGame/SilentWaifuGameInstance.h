
#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SilentWaifuGameInstance.generated.h"


class USilentWaifuSaveGame;
class ASilentWaifuGameMode;

UCLASS()
class SILENTWAIFU_2_0_API USilentWaifuGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	virtual void Init() override;
	
	void SaveMoney(int const Money) const;

	void LoadMoney();
private:

	UPROPERTY()
	FString SlotName = FString("Slot1");
	
	UPROPERTY()
	USilentWaifuSaveGame* SaveGame;
	
	UPROPERTY()
	ASilentWaifuGameMode* GameMode;
};
