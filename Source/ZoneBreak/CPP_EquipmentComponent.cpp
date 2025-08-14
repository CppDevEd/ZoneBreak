//Engine imports
#include "CPP_EquipmentComponent.h"

//Component imports

//Other imports
#include "CPP_DefaultKnife.h"
#include "CPP_WeaponBase.h"

#include "PrimaryWeaponSlotWidget.h"


UCPP_EquipmentComponent::UCPP_EquipmentComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
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

//Checks if primary weapon slot is filled, if so, equip weapon which occupies it
void UCPP_EquipmentComponent::EquipPrimary()
{
	if (!PrimaryWeaponSlot) return;

	//Temp variable
	class ACPP_WeaponBase* CurrentWeapon = nullptr;

	//Looping primary weapon slot
	for (class ACPP_WeaponBase* CurrentPrimary : PrimaryWeaponSlot->WeaponSlotSizeData.StoredWeapons)
	{
         //Parsing over nullptr primary entries
		if (!CurrentPrimary) continue;
		
		//Setting temp variable
		CurrentWeapon = CurrentPrimary;
	}

	//Checking current equiped item
	if (EquipType != EEquipType::PrimaryWeapon)
	{
		//Setting equip type
		EquipType = EEquipType::PrimaryWeapon;

		//Equiping target primary weapon
		CurrentWeapon->EquipWeapon(CurrentWeapon);

		//Setting pointer to current equiped item
		CharacterEquipStates.CurrentItem = CurrentWeapon;
	}
	else
	{
		//Resetting equip type
		EquipType = EEquipType::None;

		//Unequiping primary weapon
		CurrentWeapon->UnEquipWeapon(CurrentWeapon);

		//Nulling current item after de-equip
		CharacterEquipStates.CurrentItem = nullptr;
		CurrentWeapon = nullptr;
	}
}

void UCPP_EquipmentComponent::GetPrimarySlot(class UPrimaryWeaponSlotWidget* PrimaryWeaponSlotClass)
{
	if (!PrimaryWeaponSlotClass) return;

	PrimaryWeaponSlot = PrimaryWeaponSlotClass;
}