#pragma once

#include "FEventObjectView.generated.h"

class IEventObjectInterface;

USTRUCT(BlueprintType)
struct FEventObjectView
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly)
	TScriptInterface<IEventObjectInterface> Interface;
	
	UPROPERTY(BlueprintReadOnly)
	FGuid Id;
};
