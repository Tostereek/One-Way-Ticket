// Pietrasy's code.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WraithSpawner.generated.h"

class AWraithBase;

UCLASS()
class ONEWAYTICKET_API AWraithSpawner : public AActor
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	
	void RegisterWraith();
	
	UFUNCTION(BlueprintCallable)
	void SpawnWraith();
	
protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AWraithBase> WraithClass;
};
