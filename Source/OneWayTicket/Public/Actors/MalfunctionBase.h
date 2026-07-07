// Pietrasy's code.

#pragma once

#include "CoreMinimal.h"
#include "EventObject.h"
#include "MalfunctionBase.generated.h"

enum class EDevice : uint8;

UCLASS()
class ONEWAYTICKET_API AMalfunctionBase : public AEventObject
{
	GENERATED_BODY()
public:
	AMalfunctionBase();
	
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, Category="Malfunction");
	EDevice DeviceName;
	
	UPROPERTY(EditDefaultsOnly, Category="Malfunction", meta = (Categories = "EventObject.Malfunction"));
	FGameplayTag DeviceTag;
	
	virtual FName GetEventObjectName_Implementation() override;
	virtual FGameplayTag GetEventObjectTagType_Implementation() override;
};
