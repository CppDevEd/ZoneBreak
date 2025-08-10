//Engine imports
#include "CPP_M4CarabineRifle.h"

ACPP_M4CarabineRifle::ACPP_M4CarabineRifle()
{
	
}

void ACPP_M4CarabineRifle::OnWeaponCollect(class ACPP_Survivor* _Insigator)
{
	if (!_Insigator) return; 

	//Passing over class data
	GetWeaponType(this);
}
