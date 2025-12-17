
#include "Character/Abilities/AbilityComponent_Base.h"


UAbilityComponent_Base::UAbilityComponent_Base()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UAbilityComponent_Base::BeginPlay()
{
	Super::BeginPlay();
}

