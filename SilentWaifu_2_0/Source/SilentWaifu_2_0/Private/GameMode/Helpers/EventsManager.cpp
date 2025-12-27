
#include "GameMode/Helpers/EventsManager.h"


void UEventsManager::Init(const FDateTime& NewEventStartTime, const FDateTime& NewEventEndTime)
{
	EventStartTime = NewEventStartTime;
	EventEndTime = NewEventEndTime;
}


void UEventsManager::HandleEvent()
{
	FDateTime CurrentTime = FDateTime::Now();
	if (CurrentTime > EventEndTime)
	{
		OnEventEndedDelegate.Broadcast();
		HasEventStartedDelegate.Broadcast(false);
		return;
	}
	if (CurrentTime < EventStartTime)
	{
		FTimespan TimeLeft = EventStartTime - CurrentTime;
		TimeLeftUntilEventStart = TimeLeft.GetTotalSeconds();
		GetWorld()->GetTimerManager().SetTimer(EventStartTimer, this, &UEventsManager::HandleEventStart, .1f, false, TimeLeftUntilEventStart);
		HasEventStartedDelegate.Broadcast(false);
		return;
	}
	FTimespan TimeLeft = EventEndTime - CurrentTime;
	TimeLeftUntilEventEnd = TimeLeft.GetTotalSeconds();
	GetWorld()->GetTimerManager().SetTimer(EventEndTimer, this, &UEventsManager::HandleEventEnd, .1f, false, TimeLeftUntilEventEnd);
	HasEventStartedDelegate.Broadcast(true);
}


void UEventsManager::HandleEventStart()
{
	GetWorld()->GetTimerManager().ClearTimer(EventStartTimer);
	HasEventStartedDelegate.Broadcast(true);
	OnEventStartedDelegate.Broadcast(EventEndTime);
}


void UEventsManager::HandleEventEnd()
{
	GetWorld()->GetTimerManager().ClearTimer(EventEndTimer);
	HasEventStartedDelegate.Broadcast(false);
	OnEventEndedDelegate.Broadcast();
}


FDateTime UEventsManager::GetEventStartTime() const
{
	return EventStartTime;
}


FDateTime UEventsManager::GetEventEndTime() const
{
	return EventEndTime;
}



