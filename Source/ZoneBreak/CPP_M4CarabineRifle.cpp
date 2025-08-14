//Engine imports
#include "CPP_M4CarabineRifle.h"

ACPP_M4CarabineRifle::ACPP_M4CarabineRifle()
{
	//Passing over class data
     GetWeaponType(this);
}

//Checks if instances of this class are every overlapped
void ACPP_M4CarabineRifle::OnWeaponCollect(class ACPP_Survivor* _Insigator)
{
	if (!_Insigator) return; 

	//Adding weapon to character if possible
	AddWeaponToCharacter(this, _Insigator);
}
