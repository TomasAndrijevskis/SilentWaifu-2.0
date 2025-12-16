
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
		GetWorld()->GetTimerManager().SetTimer(EventStartTimer, this, &UEventsManager::SetTimerUntilEventStarts, 1, true, 0);
		HasEventStartedDelegate.Broadcast(false);
		return;
	}
	GetWorld()->GetTimerManager().SetTimer(EventEndTimer, this, &UEventsManager::SetTimerUntilEventEnds, 1, true, 0);
	FTimespan TimeLeft = EventEndTime - CurrentTime;
	TimeLeftUntilEventEnd = TimeLeft.GetTotalSeconds();
	HasEventStartedDelegate.Broadcast(true);
}


void UEventsManager::SetTimerUntilEventStarts()
{
	if (TimeLeftUntilEventStart > 0) TimeLeftUntilEventStart--;
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(EventStartTimer);
		HasEventStartedDelegate.Broadcast(true);
		OnEventStartedDelegate.Broadcast(EventEndTime);
	}
}


void UEventsManager::SetTimerUntilEventEnds()
{
	if (TimeLeftUntilEventEnd > 0) TimeLeftUntilEventEnd--;
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(EventEndTimer);
		HasEventStartedDelegate.Broadcast(false);
		OnEventEndedDelegate.Broadcast();
	}
}


FDateTime UEventsManager::GetEventStartTime() const
{
	return EventStartTime;
}


FDateTime UEventsManager::GetEventEndTime() const
{
	return EventEndTime;
}



