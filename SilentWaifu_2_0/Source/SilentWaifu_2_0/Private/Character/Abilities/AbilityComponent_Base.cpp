
#include "Character/Abilities/AbilityComponent_Base.h"
#include "Character/CharacterTemplate.h"
#include "GameMode/SilentWaifuGameMode.h"
#include "Kismet/GameplayStatics.h"


void UAbilityComponent_Base::BeginPlay()
{
	Super::BeginPlay();
	SetManagers();
	if (!CharactersManager || !MoneyManager) return;
	CharacterRef = Cast<ACharacterTemplate>(GetOwner());
	if (!CharacterRef) return;
	OnCharacterIdRequestDelegate.AddUniqueDynamic(this, &UAbilityComponent_Base::SetCharacterID);
	OnAbilityActivatedDelegate.AddUniqueDynamic(this, &UAbilityComponent_Base::Action);
}


void UAbilityComponent_Base::SetManagers()
{
	const ASilentWaifuGameMode* GameMode = Cast<ASilentWaifuGameMode>(UGameplayStatics::GetGameMode(this));
	if (!GameMode) return;
	CharactersManager = GameMode->CharactersManager;
	MoneyManager = GameMode->MoneyManager;
}


void UAbilityComponent_Base::SetCharacterID(int NewId)
{
	CharacterId = NewId;
}


int UAbilityComponent_Base::GetCharacterID() const
{
	return CharacterId;
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



