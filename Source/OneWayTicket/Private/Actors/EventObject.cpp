// Pietrasy's code.


#include "Actors/EventObject.h"

#include "TicketTags.h"
#include "Managers/EventManager.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "OneWayTicket/OneWayTicket.h"


AEventObject::AEventObject()
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EventObjectBase"));
	StaticMeshComponent->SetMobility(EComponentMobility::Movable);
	SetRootComponent(StaticMeshComponent);	
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioComponent->SetupAttachment(StaticMeshComponent);
	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraSystem"));
	NiagaraComponent->SetupAttachment(StaticMeshComponent);
}

void AEventObject::BeginPlay()
{
	Super::BeginPlay();
	
	if (!Id.IsValid())
	{
		Id = FGuid::NewGuid();
	}
	
	RegisterActor();
	AddTag(TicketTags::EventObject_State_Deactivated);
}

void AEventObject::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	
	UnregisterActor();
}

bool AEventObject::IsEventObjectActive_Implementation()
{
	return EventObjectTags.HasTag(TicketTags::EventObject_State_Activated);
}

void AEventObject::PostEditImport()
{
	Super::PostEditImport();
	
#if WITH_EDITOR
	Id = FGuid::NewGuid();
#endif
}

void AEventObject::Interact(AActor* InInstigator)
{
	OnInteraction.Broadcast(InInstigator);
}

const FGameplayTagContainer& AEventObject::GetEventObjectTags() const
{
	return EventObjectTags;
}

void AEventObject::AddTag(FGameplayTag InTag)
{
	EventObjectTags.AddTag(InTag);
}

void AEventObject::RemoveTag(FGameplayTag InTag)
{
	EventObjectTags.RemoveTag(InTag);
}

bool AEventObject::HasEventObjectTag(FGameplayTag InTag) const
{
	return EventObjectTags.HasTag(InTag);
}

FGuid AEventObject::GetEventObjectId_Implementation()
{
	return Id;
}

void AEventObject::ActivateEventObject()
{
	if (HasEventObjectTag(TicketTags::EventObject_State_Activated))
	{
		return;
	}
	
	RemoveTag(TicketTags::EventObject_State_Deactivated);
	AddTag(TicketTags::EventObject_State_Activated);
	AudioComponent->SetSound(SoundWhileActive);
	UGameplayStatics::PlaySoundAtLocation(this, SoundWhileActive, GetActorLocation(), GetActorRotation());
	NiagaraComponent->SetAsset(ParticleWhileActive);
	OnActivated();
	OnActiveEventObject.Broadcast();
}

void AEventObject::DeactivateEventObject()
{
	if (HasEventObjectTag(TicketTags::EventObject_State_Deactivated))
	{
		return;
	}
	
	RemoveTag(TicketTags::EventObject_State_Activated);
	AddTag(TicketTags::EventObject_State_Deactivated);
	AudioComponent->SetSound(SoundWhileInactive);
	UGameplayStatics::PlaySoundAtLocation(this, SoundWhileInactive, GetActorLocation(), GetActorRotation());
	NiagaraComponent->SetAsset(ParticleWhileInactive);
	OnDeactivated();
	OnDeactivateEventObject.Broadcast(this);
}

void AEventObject::SetEventActorMesh(UStaticMesh* InStaticMesh) const
{
	StaticMeshComponent->SetStaticMesh(InStaticMesh);
}


void AEventObject::RegisterActor()
{
	UWorld* World = GetWorld();
	if (!IsValid(World))
	{
		UE_VLOG_UELOG(this, LogOneWayTicket, Error, TEXT("[%hs] - Invalid World!"), __FUNCTION__);
		return;
	}
	
	EventSubsystem = World->GetSubsystem<UEventManager>();

	if (!IsValid(EventSubsystem))
	{
		UE_VLOG_UELOG(this, LogEventManager, Error, TEXT("[%hs] - Invalid EventSubsystem!"), __FUNCTION__);
		return;
	}
	
	EventSubsystem->RegisterEventObject(this);
}

void AEventObject::UnregisterActor()
{
	UWorld* World = GetWorld();
	if (!IsValid(World))
	{
		UE_VLOG_UELOG(this, LogOneWayTicket, Error, TEXT("[%hs] - Invalid World!"), __FUNCTION__);
	}
	
	if (!IsValid(EventSubsystem))
	{
		UE_VLOG_UELOG(this, LogEventManager, Error, TEXT("[%hs] - Invalid EventSubsystem!"), __FUNCTION__);
	}
	
	EventSubsystem->UnregisterEventObject(this);
}
