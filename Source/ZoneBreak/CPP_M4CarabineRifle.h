#pragma once

//Engine imports
#include "CoreMinimal.h"
#include "CPP_WeaponBase.h"
#include "CPP_M4CarabineRifle.generated.h"


UCLASS()
class ZONEBREAK_API ACPP_M4CarabineRifle : public ACPP_WeaponBase
{
	GENERATED_BODY()
	
private:    
	    ///<Pirvate M4CarabineRifle functions && components>
	ACPP_M4CarabineRifle();

protected:
	        ///<Protected M4CarabineRifle functions && components>

	//Interface override function, triggers pick-up logic && attachment logic
	virtual void OnWeaponCollect(class ACPP_Survivor* _Instigator);
};
