// Pietrasy's code.


#include "Managers/EventManager.h"

#include "Actors/EventObject.h"
#include "Actors/WraithSpawner.h"
#include "OneWayTicket/OneWayTicket.h"

void UEventManager::RegisterEventObject(AEventObject* InEventObject)
{
	if (!IsValid(InEventObject))
	{
		UE_VLOG_UELOG(this, LogEventManager, Error, TEXT("[%hs] - EventObject isn't valid!"), __FUNCTION__);
		return;
	}
	EventObjects.Add(InEventObject->Execute_GetEventObjectId(InEventObject), InEventObject);
	
	InEventObject->OnActiveEventObject.AddUObject(this, &UEventManager::OnActivationEventObject, InEventObject);
	InEventObject->OnDeactivateEventObject.AddDynamic(this, &UEventManager::OnDeactivationEventObject);
	
	OnRegisterEventObject.Broadcast(CreateEventObjectView(InEventObject));
}

void UEventManager::UnregisterEventObject(AEventObject* InEventObject)
{
	EventObjects.Remove(InEventObject->Execute_GetEventObjectId(InEventObject));
	OnUnregisterEventObject.Broadcast(InEventObject->Execute_GetEventObjectId(InEventObject));
}

void UEventManager::OnActivationEventObject(AEventObject* InEventObject)
{
	OnUpdateEventObject.Broadcast(InEventObject->Execute_GetEventObjectId(InEventObject));
	OnActivatedAnomaly.Broadcast(InEventObject);
}

void UEventManager::OnDeactivationEventObject(AEventObject* InEventObject)
{
	OnUpdateEventObject.Broadcast(InEventObject->Execute_GetEventObjectId(InEventObject));
	OnDeactivatedAnomaly.Broadcast(InEventObject);
}

void UEventManager::SpawnWraith()
{
	if (WraithSpawners.IsEmpty())
	{
		UE_VLOG_UELOG(this, LogEventManager, Error,	TEXT("[%hs] - WraithSpawners is empty!"), __FUNCTION__);
		return;
	}
	
	const uint8 InIndex = FMath::RandRange(0, WraithSpawners.Num() - 1);
	WraithSpawners[InIndex]->SpawnWraith();
}

void UEventManager::RegisterWraithSpawner(AWraithSpawner* InSpawner)
{
	WraithSpawners.Add(InSpawner);
}

FEventObjectView UEventManager::FindEventObjectViewById(FGuid InId)
{;
	TWeakObjectPtr<AEventObject> InWeakPtr = *EventObjects.Find(InId);

	if (!InWeakPtr.IsValid())
	{
		UE_VLOG_UELOG(this, LogEventManager, Error, TEXT("[%hs] - Invalid InWeakPtr!"), __FUNCTION__);
		return FEventObjectView();
	}
	
	AEventObject* Object = InWeakPtr.Get();
	return CreateEventObjectView(Object); 
}

void UEventManager::FindEventObjectsByTags(const FGameplayTagContainer& InTags, TArray<AEventObject*>& OutResults) const
{
	OutResults.Reset();

	for (const auto Pair : EventObjects)
	{
		const TWeakObjectPtr<AEventObject>& WeakPtr = Pair.Value;

		if (!WeakPtr.IsValid())
		{
			continue;
		}
		
		AEventObject* Object = WeakPtr.Get();

		if (!IsValid(Object))
		{
			continue;
		}
		
		const FGameplayTagContainer& Tags = Object->GetEventObjectTags();

		if (Tags.HasAny(InTags))
		{
			OutResults.Add(Object);
		}
	}
}

void UEventManager::FindEventObjectsByTags(const FGameplayTag& InTag, TArray<AEventObject*>& OutResults) const
{
	FGameplayTagContainer Container;
	Container.AddTag(InTag);

	FindEventObjectsByTags(Container, OutResults);
}

void UEventManager::FindEventObjectViewsByTags(const FGameplayTagContainer& InTags,
	TArray<FEventObjectView>& OutResults)
{
	OutResults.Reset();

	for (const auto Pair : EventObjects)
	{
		const TWeakObjectPtr<AEventObject>& WeakPtr = Pair.Value;

		if (!WeakPtr.IsValid())
		{
			continue;
		}
		
		AEventObject* Object = WeakPtr.Get();

		if (!IsValid(Object))
		{
			continue;
		}
		
		const FGameplayTagContainer& Tags = Object->GetEventObjectTags();

		if (Tags.HasAll(InTags))
		{
			OutResults.Add(CreateEventObjectView(Object));
		}
	}
}

void UEventManager::FindEventObjectViewsByTags(const FGameplayTag& InTag, TArray<FEventObjectView>& OutResults)
{
	FGameplayTagContainer Container;
	Container.AddTag(InTag);

	FindEventObjectViewsByTags(Container, OutResults);
}

FEventObjectView UEventManager::CreateEventObjectView(AEventObject* InEventObject)
{
	FEventObjectView View;
	
	TScriptInterface<IEventObjectInterface> Interface;
	Interface.SetObject(InEventObject);
	Interface.SetInterface(Cast<IEventObjectInterface>(InEventObject));
	
	View.Id = InEventObject->Execute_GetEventObjectId(InEventObject);
	View.Interface = Interface;
	
	return View;
}
