#pragma once

//Engine imports
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CPP_ICollectable.generated.h"

UINTERFACE(MinimalAPI)
class UCPP_ICollectable : public UInterface
{
	GENERATED_BODY()
};


class ZONEBREAK_API ICPP_ICollectable
{
	GENERATED_BODY()

public:
    //Pure virual functions for collection event logic
	virtual void OnWeaponCollect(class ACPP_Survivor* _Instigator) = 0;
};
