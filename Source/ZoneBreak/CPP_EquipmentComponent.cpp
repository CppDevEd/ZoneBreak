//Engine imports
#include "CPP_EquipmentComponent.h"

//Component imports

//Other imports
#include "CPP_DefaultKnife.h"

UCPP_EquipmentComponent::UCPP_EquipmentComponent()
{
	
	PrimaryComponentTick.bCanEverTick = true;

}

void UCPP_EquipmentComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCPP_EquipmentComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool UCPP_EquipmentComponent::CurrentEquipment(EEquipType Type) const
{
	return EquipType == Type;
}

               /// <Equip functions && logic>
void UCPP_EquipmentComponent::EquipKnife()
{
	if (!Knife) return;
	
	//Checking current equip type
	if (EquipType != EEquipType::Knife)
	{
		//Equiping knife to player character
		Knife->EquipKnife(Knife);

		//Setting current equiped item
		EquipType = EEquipType::Knife;
		//populating item pointer with current equiped item
		CharacterEquipStates.CurrentItem = Knife;
	}
	else
	{
		//Setting equip type back to default
		EquipType = EEquipType::None;

		//Calling unequip
		Knife->UnEquipKnife(Knife);

		//Setting current equip item to null
		CharacterEquipStates.CurrentItem = nullptr;
	}
}
void UCPP_EquipmentComponent::GetKnifeClass(class ACPP_DefaultKnife* KnifeClass)
{
	if (!KnifeClass) return;

	Knife = KnifeClass;
}
