
#pragma once

#include "CoreMinimal.h"


UENUM(BlueprintType)
enum ERarities
{
	Common UMETA(DisplayName = "Common"),
	Rare UMETA(DisplayName = "Rare"),
	VeryRare UMETA(DisplayName = "Very Rare"),
	Elite UMETA(DisplayName = "Elite"),
	Legendary UMETA(DisplayName = "Legendary"),
	Event UMETA(DisplayName = "Event"),
};