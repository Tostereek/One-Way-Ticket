// Pietrasy's code.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperFlipbookComponent.h"
#include "WraithBase.generated.h"

UCLASS()
class ONEWAYTICKET_API AWraithBase : public AActor
{
	GENERATED_BODY()

public:
	AWraithBase();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wraith")
	TObjectPtr<UPaperFlipbookComponent> WraithFlipbook;
	
	UPROPERTY(BlueprintReadOnly, Category = "Wraith")
	TObjectPtr<USceneComponent> WraithRootComponent;
};
