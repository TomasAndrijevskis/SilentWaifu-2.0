
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DataTables/AbilityData.h"
#include "AbilityComponent_Base.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SILENTWAIFU_2_0_API UAbilityComponent_Base : public UActorComponent
{
	GENERATED_BODY()

public:
	
	UAbilityComponent_Base();
	
protected:
	
	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere)
	bool IsAbilityActive = false;

	UPROPERTY(VisibleAnywhere)
	FString Description;

	UPROPERTY(VisibleAnywhere)
	UTexture2D* Icon;
	
	//UPROPERTY(EditAnywhere)
	//int Duration_Hours;// only first ability

	UPROPERTY(EditAnywhere)
	FAbilityData AbilityData;

	UPROPERTY(EditAnywhere)
	FString AbilityName;
};
