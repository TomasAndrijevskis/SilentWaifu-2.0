
#pragma once

#include "CoreMinimal.h"
#include "EventsManager.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHasEventStartedSignature, bool, HasStarted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEventStartedSignature, const FDateTime&, EventEndTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEventEndedSignature);
UCLASS()
class SILENTWAIFU_2_0_API UEventsManager : public UObject
{
	GENERATED_BODY()

public:

	void Init(const FDateTime& NewEventStartTime, const FDateTime& NewEventEndTime);

	void HandleEvent();
	
	FDateTime GetEventStartTime() const;

	FDateTime GetEventEndTime() const;

	FHasEventStartedSignature HasEventStartedDelegate;

	FOnEventStartedSignature OnEventStartedDelegate;

	FOnEventEndedSignature OnEventEndedDelegate;
	
private:

	UFUNCTION()
	void SetTimerUntilEventStarts();

	UFUNCTION()
	void SetTimerUntilEventEnds();
	
	FDateTime EventStartTime;

	FDateTime EventEndTime;
	
	FTimerHandle EventStartTimer;

	FTimerHandle EventEndTimer;
	
	int TimeLeftUntilEventStart = 0;

	int TimeLeftUntilEventEnd = 0;
};
