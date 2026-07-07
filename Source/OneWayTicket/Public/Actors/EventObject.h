// Pietrasy's code.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "Interfaces/EventObjectInterface.h"
#include "NiagaraComponent.h"
#include "EventObject.generated.h"

class UEventManager;

DECLARE_MULTICAST_DELEGATE(FOnActivateEventObject);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDeactivateEventObjectBlueprint, AEventObject*, EventObject);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteraction, AActor*, Instigator);

UCLASS(Abstract)
class ONEWAYTICKET_API AEventObject : public AActor, public IEventObjectInterface
{
	GENERATED_BODY()
	
public:
	AEventObject();
	
	FOnActivateEventObject OnActiveEventObject;
	UPROPERTY(BlueprintAssignable)
	FOnDeactivateEventObjectBlueprint OnDeactivateEventObject;
	FOnInteraction OnInteraction;
	
	virtual void PostEditImport() override;
	
	UFUNCTION(BlueprintCallable, Category="EventObject")
	void Interact(AActor* InInstigator);
	
	const FGameplayTagContainer& GetEventObjectTags() const;
	void AddTag(FGameplayTag InTag);
	void RemoveTag(FGameplayTag InTag);
	bool HasEventObjectTag(FGameplayTag InTag) const;
	
	// ~~ IEventObjectInterface ~~
	virtual FGuid GetEventObjectId_Implementation() override;
	virtual bool IsEventObjectActive_Implementation() override;
	// ~~ IEventObjectInterface ~~
	
	UFUNCTION(BlueprintCallable, Category="EventObject")
	void ActivateEventObject();
	
	UFUNCTION(BlueprintCallable, Category="EventObject")
	void DeactivateEventObject();
	
	UFUNCTION(BlueprintCallable, Category="EventObject")
	void SetEventActorMesh(UStaticMesh* InStaticMesh) const;
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	UPROPERTY(EditAnywhere, Category="EventObject|Sounds")
	TObjectPtr<USoundBase> SoundWhileActive;
	UPROPERTY(EditAnywhere, Category="EventObject|Sounds")
	TObjectPtr<USoundBase> SoundWhileInactive;
	UPROPERTY(EditAnywhere, Category="EventObject|Sounds")
	TObjectPtr<USoundBase> ActivationSound;
	UPROPERTY(EditAnywhere, Category="EventObject|Sounds")
	TObjectPtr<USoundBase> DeactivationSound;
	
	UPROPERTY(EditAnywhere, Category="EventObject|Particles")
	TObjectPtr<UNiagaraSystem> ParticleWhileActive;
	UPROPERTY(EditAnywhere, Category="EventObject|Particles")
	TObjectPtr<UNiagaraSystem> ParticleWhileInactive;
	UPROPERTY(EditAnywhere, Category="EventObject|Particles")
	TObjectPtr<UNiagaraSystem> ActivationParticle;
	UPROPERTY(EditAnywhere, Category="EventObject|Particles")
	TObjectPtr<UNiagaraSystem> DeactivationParticle;
	
	UPROPERTY(EditDefaultsOnly, Category="EventObject")
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
	UPROPERTY(EditDefaultsOnly, Category="EventObject")
	TObjectPtr<UAudioComponent> AudioComponent;
	UPROPERTY(EditDefaultsOnly, Category="EventObject")
	TObjectPtr<UNiagaraComponent> NiagaraComponent;
	
	UFUNCTION(BlueprintImplementableEvent, Category="EventObject")
	void OnActivated();
	
	UFUNCTION(BlueprintImplementableEvent, Category="EventObject")
	void OnDeactivated();
	
private:
	UPROPERTY()
	UEventManager* EventSubsystem = nullptr;
	
	FGameplayTagContainer EventObjectTags;
	
	FGuid Id;
	
	void RegisterActor();
	void UnregisterActor();
};
