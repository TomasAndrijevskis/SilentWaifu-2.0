
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SilentWaifuGameMode.generated.h"


class USoundManager;
class UBackgroundManager;
class UCharactersManager;
class UMoneyManager;
class UWidgetReferenceDataAsset;
class UMainScreen;
class ACharacterTemplate;
class USilentWaifuGameInstance;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCharactersLoadedSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnShopCreatedSignature);
UCLASS()
class SILENTWAIFU_2_0_API ASilentWaifuGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	
	void OnCharacterSpawned(const int CurrentSpawnPosition) const;

	void OnCharacterRemovedDelegate(const int Position) const;

	FDateTime GetShutdownTime() const;

	void SetShutdownTime(const FDateTime& NewLastJoinTime);
	
	UPROPERTY()
	UMoneyManager* MoneyManager;

	UPROPERTY()
	UCharactersManager* CharactersManager;

	UPROPERTY()
	UBackgroundManager* BackgroundManager;

	UPROPERTY()
	USoundManager* SoundManager;
	
	UPROPERTY(EditAnywhere)
	UWidgetReferenceDataAsset* WidgetReferences;
	
	FOnCharactersLoadedSignature OnCharactersLoadedDelegate;
	
	FOnShopCreatedSignature OnShopCreatedDelegate;

	
protected:

	virtual void BeginPlay() override;
	
private:

	void HandleGameLoad();
	
	void CreateMainScreenWidget();

	void SetInputSettings() const;

	void HandleManagers();
	
	UPROPERTY()
	USilentWaifuGameInstance* GameInstance;

	UPROPERTY(EditAnywhere)
	UDataTable* CharacterDataTable;

	UPROPERTY(EditAnywhere)
	UDataTable* BackgroundDataTable;

	UPROPERTY(EditAnywhere)
	UDataTable* MoneyLimitsDataTable;

	UPROPERTY(EditAnywhere)
	USoundMix* MusicMixModifier;

	UPROPERTY(EditAnywhere)
	USoundMix* SFXMixModifier;

	UPROPERTY(EditAnywhere)
	USoundClass* MusicClass;

	UPROPERTY(EditAnywhere)
	USoundClass* SFXClass;
	
	FDateTime ShutdownTime;
};

