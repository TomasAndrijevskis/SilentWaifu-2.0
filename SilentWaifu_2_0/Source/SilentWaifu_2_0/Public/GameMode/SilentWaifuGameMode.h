
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SilentWaifuGameMode.generated.h"


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
	
	UPROPERTY()
	UMoneyManager* MoneyManager;

	UPROPERTY()
	UCharactersManager* CharactersManager;
	
	UPROPERTY(EditAnywhere)
	UWidgetReferenceDataAsset* WidgetReferences;
	
	FOnCharactersLoadedSignature OnCharactersLoadedDelegate;
	
	FOnShopCreatedSignature OnShopCreatedDelegate;

	UPROPERTY(EditAnywhere)
	UDataTable* CharacterDataTable;
	
protected:

	virtual void BeginPlay() override;
	
private:

	void HandleGameLoad();
	
	void CreateMainScreenWidget();

	void SetInputSettings() const;
	
	UPROPERTY()
	USilentWaifuGameInstance* GameInstance;
	
};
