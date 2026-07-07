// Pietrasy's code.


#include "Actors/WraithSpawner.h"

#include "Actors/WraithBase.h"
#include "Managers/EventManager.h"
#include "OneWayTicket/OneWayTicket.h"

void AWraithSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	RegisterWraith();
}

void AWraithSpawner::RegisterWraith()
{
	UWorld* World = GetWorld();
	if (!IsValid(World))
	{
		UE_VLOG_UELOG(this, LogOneWayTicket, Error, TEXT("[%hs] - Invalid World!"), __FUNCTION__);
		return;
	}
	
	UEventManager* EventManager = World->GetSubsystem<UEventManager>();

	if (!IsValid(EventManager))
	{
		UE_VLOG_UELOG(this, LogEventManager, Error, TEXT("[%hs] - Invalid EventSubsystem!"), __FUNCTION__);
		return;
	}
	
	EventManager->RegisterWraithSpawner(this);
}

void AWraithSpawner::SpawnWraith()
{
	UWorld* World = GetWorld();
	if (!IsValid(World))
    {
    	UE_VLOG_UELOG(this, LogOneWayTicket, Error, TEXT("[%hs] - Invalid World!"), __FUNCTION__);
    	return;
    }
    	
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	const FVector SpawnLocation = GetActorLocation();
	const FRotator SpawnRotation = GetActorRotation();
	
	World->SpawnActor<AWraithBase>(WraithClass, SpawnLocation, SpawnRotation, SpawnParameters);
	UE_VLOG_UELOG(this, LogOneWayTicket, Log, TEXT("[%hs] - Wraith has been spawned!"), __FUNCTION__);
}
