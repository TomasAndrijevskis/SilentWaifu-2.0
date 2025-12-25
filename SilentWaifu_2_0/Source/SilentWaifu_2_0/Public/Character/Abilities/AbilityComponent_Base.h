
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AbilityComponent_Base.generated.h"


class ACharacterTemplate;
class UMoneyManager;
class UCharactersManager;
struct FAbilityData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAbilityActivatedSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterIdRequestSignature, int, ID);
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SILENTWAIFU_2_0_API UAbilityComponent_Base : public UActorComponent
{
	GENERATED_BODY()

public:

	FOnAbilityActivatedSignature OnAbilityActivatedDelegate;

	FOnCharacterIdRequestSignature OnCharacterIdRequestDelegate;
	
	UFUNCTION()
	void SetCharacterID(int NewId);
	
protected:
	
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void Action() {};
	
	bool IsAbilityActive() const;

	FString GetAbilityDescription() const;

	UTexture2D* GetAbilityIcon() const;

	UPROPERTY()
	UCharactersManager* CharactersManager;

	UPROPERTY()
	UMoneyManager* MoneyManager;
	
private:

	//UPROPERTY(EditAnywhere)
	//int Duration_Hours;// only first ability
	
	void SetManagers();
	
	UPROPERTY(VisibleAnywhere)
	bool bIsAbilityActive = false;

	UPROPERTY(VisibleAnywhere)
	FString Description;

	UPROPERTY(VisibleAnywhere)
	UTexture2D* Icon;

	UPROPERTY(VisibleAnywhere)
	FString AbilityName;

	UPROPERTY()
	ACharacterTemplate* CharacterRef;

	int CharacterId;
};
