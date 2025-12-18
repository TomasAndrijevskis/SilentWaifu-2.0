
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AbilityComponent_Base.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SILENTWAIFU_2_0_API UAbilityComponent_Base : public UActorComponent
{
	GENERATED_BODY()

protected:
	
	virtual void BeginPlay() override;

	virtual void Action() {};
	
	bool IsAbilityActive() const;

	FString GetAbilityDescription() const;

	UTexture2D* GetAbilityIcon() const;
	
private:

	UPROPERTY(VisibleAnywhere)
	bool bIsAbilityActive = false;

	UPROPERTY(VisibleAnywhere)
	FString Description;

	UPROPERTY(VisibleAnywhere)
	UTexture2D* Icon;
	
	//UPROPERTY(EditAnywhere)
	//int Duration_Hours;// only first ability

	UPROPERTY(VisibleAnywhere)
	FString AbilityName;
};
