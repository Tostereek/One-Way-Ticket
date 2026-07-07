// Pietrasy's code.


#include "Actors/AnomalyBase.h"

#include "TicketTags.h"
#include "Data/EAnomaly.h"
#include "OneWayTicket/OneWayTicket.h"

AAnomalyBase::AAnomalyBase()
{
	AddTag(TicketTags::EventObject_Anomaly);
}

void AAnomalyBase::BeginPlay()
{
	Super::BeginPlay();

	if (!AnomalyTag.IsValid() || AnomalyName == EAnomaly::Null)
	{
		UE_VLOG_UELOG(this, LogEventObject, Error,  TEXT("[%s] - Isn't properly setup!"), *GetName());
		return;
	}
	
	AddTag(AnomalyTag);
}

FName AAnomalyBase::GetEventObjectName_Implementation()
{
	return UEnum::GetValueAsName(AnomalyName);
}

FGameplayTag AAnomalyBase::GetEventObjectTagType_Implementation()
{
	return AnomalyTag;
}