// Pietrasy's code.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Data/FEventObjectView.h"
#include "Subsystems/WorldSubsystem.h"
#include "EventManager.generated.h"

class AWraithSpawner;
class AEventObject;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpdateEventObject, FGuid, EventObjectID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActivatedAnomaly, AActor*, ActivatedEventActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDeactivatedAnomaly, AActor*, ActivatedEventActor);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnRegisterEventObject, const FEventObjectView&);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnUnregisterEventObject, FGuid);

/**
 * 
 */
UCLASS()
class ONEWAYTICKET_API UEventManager : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable, Category="EventSubsystem")
	FOnUpdateEventObject OnUpdateEventObject;
	
	UPROPERTY(BlueprintAssignable, Category="EventSubsystem")
	FOnActivatedAnomaly OnActivatedAnomaly;
	
	UPROPERTY(BlueprintAssignable, Category="EventSubsystem")
	FOnDeactivatedAnomaly OnDeactivatedAnomaly;
	
	FOnRegisterEventObject OnRegisterEventObject;
	FOnUnregisterEventObject OnUnregisterEventObject;
	
	UFUNCTION(BlueprintCallable, Category="EventSubsystem")
	FEventObjectView FindEventObjectViewById(FGuid InId);
	
	UFUNCTION(BlueprintCallable, Category="EventSubsystem")
	void FindEventObjectsByTags(const FGameplayTagContainer& InTags, TArray<AEventObject*>& OutResults) const;
	void FindEventObjectsByTags(const FGameplayTag& InTag, TArray<AEventObject*>& OutResults) const;
	
	UFUNCTION(BlueprintCallable, Category="EventSubsystem")
	void FindEventObjectViewsByTags(const FGameplayTagContainer& InTags, TArray<FEventObjectView>& OutResults);
	void FindEventObjectViewsByTags(const FGameplayTag& InTag, TArray<FEventObjectView>& OutResults);
	
	void RegisterEventObject(AEventObject* InEventObject);
	void UnregisterEventObject(AEventObject* InEventObject);
	
	void OnActivationEventObject(AEventObject* InEventObject);
	UFUNCTION()
	void OnDeactivationEventObject(AEventObject* InEventObject);
	
	UFUNCTION(BlueprintCallable)
	void SpawnWraith();
	void RegisterWraithSpawner(AWraithSpawner* InSpawner);
	
private:
	TMap<FGuid, TWeakObjectPtr<AEventObject>> EventObjects;
	TArray<TObjectPtr<AWraithSpawner>> WraithSpawners;
	
	FEventObjectView CreateEventObjectView(AEventObject* InEventObject);
};
