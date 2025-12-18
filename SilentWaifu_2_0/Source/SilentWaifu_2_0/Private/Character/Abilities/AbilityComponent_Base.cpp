
#include "Character/Abilities/AbilityComponent_Base.h"


void UAbilityComponent_Base::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Error, TEXT("UAbilityComponent_Base::BeginPlay"));
	FString Name = this->GetOwner()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("Owner Name: %s"), *Name);
}


bool UAbilityComponent_Base::IsAbilityActive() const
{
	return bIsAbilityActive;
}


FString UAbilityComponent_Base::GetAbilityDescription() const
{
	return Description;
}


UTexture2D* UAbilityComponent_Base::GetAbilityIcon() const
{
	return Icon;
}

