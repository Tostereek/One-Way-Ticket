// Pietrasy's code.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Data/EDevice.h"
#include "UObject/Interface.h"
#include "EventObjectInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UEventObjectInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ONEWAYTICKET_API IEventObjectInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	UPARAM(DisplayName="Name")
	FName GetEventObjectName();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	UPARAM(DisplayName="ID")
	FGuid GetEventObjectId();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	UPARAM(DisplayName="IsActive")
	bool IsEventObjectActive();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	UPARAM(DisplayName="TypeTag")
	FGameplayTag GetEventObjectTagType();
};
