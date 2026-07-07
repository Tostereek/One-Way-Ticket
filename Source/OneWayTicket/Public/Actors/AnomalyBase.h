// Pietrasy's code.

#pragma once

#include "CoreMinimal.h"
#include "EventObject.h"
#include "AnomalyBase.generated.h"

enum class EAnomaly : uint8;

UCLASS()
class ONEWAYTICKET_API AAnomalyBase : public AEventObject
{
	GENERATED_BODY()
	
public:
	AAnomalyBase();
	
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, Category="Anomaly")
	EAnomaly AnomalyName;
	
	UPROPERTY(EditDefaultsOnly, Category="Anomaly", meta = (Categories = "EventObject.Anomaly"));
	FGameplayTag AnomalyTag;
	
	virtual FName GetEventObjectName_Implementation() override;
	virtual FGameplayTag GetEventObjectTagType_Implementation() override;
};
