// Pietrasy's code.


#include "Actors/MalfunctionBase.h"

#include "TicketTags.h"
#include "Data/EDevice.h"
#include "OneWayTicket/OneWayTicket.h"

AMalfunctionBase::AMalfunctionBase()
{
	AddTag(TicketTags::EventObject_Malfunction);
}

void AMalfunctionBase::BeginPlay()
{
	Super::BeginPlay();
	
	if (!DeviceTag.IsValid() || DeviceName == EDevice::Null)
	{
		UE_VLOG_UELOG(this, LogEventObject, Error,  TEXT("[%s] - Isn't properly setup!"), *GetName());
		return;
	}
	
	AddTag(DeviceTag);
}

FName AMalfunctionBase::GetEventObjectName_Implementation()
{
	return UEnum::GetValueAsName(DeviceName);
}

FGameplayTag AMalfunctionBase::GetEventObjectTagType_Implementation()
{
	return DeviceTag;
}
