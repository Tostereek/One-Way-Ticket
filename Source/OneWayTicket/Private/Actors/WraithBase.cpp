// Pietrasy's code.


#include "Actors/WraithBase.h"


AWraithBase::AWraithBase()
{
	WraithRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("WraithRoot"));
	WraithFlipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("WraithFlipbook"));
	SetRootComponent(WraithRootComponent);
	WraithFlipbook->SetupAttachment(WraithRootComponent);
}
