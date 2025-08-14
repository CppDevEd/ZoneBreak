//Engine imports
#include "InventoryComponent.h"

//Component imports
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Components/Widget.h"

//Other imports
#include "InventoryWidget.h"
#include "GearSlotWidgetBase.h"
#include "CPP_Survivor.h"


UInventoryComponent::UInventoryComponent()
{	
	PrimaryComponentTick.bCanEverTick = true;
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();	

	//Creates main inventory in memory
	CreateMainInventory();
}

void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

//Called in main inventory construct
void UInventoryComponent::CreateMainInventory()
{
	//Ensuring inventory reference has been set
	if (!InventoryWidgetClass) return;
    
	//Creating inventory widget
	InventoryWidget = CreateWidget(GetWorld(), InventoryWidgetClass);

	if (!InventoryWidget) return;

	//Getting player character
	PlayerCharacter = Cast<class ACPP_Survivor>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (!PlayerCharacter) return;

	//Getting player character controller
	CharacterController = Cast<class APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (!CharacterController) return;

	//Setting inventory widget owner
	InventoryWidget->SetOwningPlayer(CharacterController);
	
	//Setting default states
	InventoryWidget->AddToViewport(true);
	InventoryWidget->SetVisibility(ESlateVisibility::Collapsed);
}

void UInventoryComponent::ToggleMainInventory()
{
	if (InventoryWidget->GetVisibility() == ESlateVisibility::Collapsed)
	{
		//Setting visibility to visible
		InventoryWidget->SetVisibility(ESlateVisibility::Visible);
		//Setting character input mode
		CharacterController->SetInputMode(FInputModeGameAndUI());
		//Setting cursor visibility
		CharacterController->SetShowMouseCursor(true);
	}
	else
	{
		//Setting visibility to collapsed
		InventoryWidget->SetVisibility(ESlateVisibility::Collapsed);
		//Setting character input mode
		CharacterController->SetInputMode(FInputModeGameOnly());
		//Setting cursor visibility
		CharacterController->SetShowMouseCursor(false);
	}
}

void UInventoryComponent::CachedInventoryData()
{
     //Casting UUserWidget pointer to inventory widget class
	class UInventoryWidget* MainInventory = Cast<class UInventoryWidget>(InventoryWidget);
   
	if (!MainInventory) return;

	//Looping children in main inventory
	for (UWidget* GetChild : MainInventory->InventoryCache()->GetAllChildren())
	{
		//Parsing over nullptr children
		if (!GetChild) continue;

		//Casting Children to gear slot widget
		class UGearSlotWidgetBase* TargetGearSlot = Cast<class UGearSlotWidgetBase>(GetChild);

		//Parsing over nullptr target gear slots
		if (!TargetGearSlot) continue;

		//Adding valid pointers to found slot children into data map
		GearSlotData.Add(TargetGearSlot, TargetGearSlot->GetStorageType());
	}
}

                  ///<Inventory logic functions>
bool UInventoryComponent::WeaponOverlapped(class ACPP_WeaponBase* Weapon)
{
	if (!Weapon) return false;

	//Checking if data map was ever populated with valid instances
	if (GearSlotData.IsEmpty()) return false;

	//Looping GearSlotData
	for (const TPair<class UGearSlotWidgetBase*, EStorageType>& Slot : GearSlotData)
	{
		//Parsing over null instances
		if (!Slot.Key) continue;

		//Checking if any slots match weapon type
		if (CheckStorageType(Weapon->GetWeaponType(Weapon), Slot.Value))
		{
			//Looping all possible entrys for weapon in target slot
			for (int32 Entries = 0; Entries < Slot.Key->WeaponSlotSizeData.StoredWeapons.Num(); Entries++)
			{
				//Checking if there are empty entries for weapon
				if (CheckWeaponSlot(Weapon, Slot.Key, Entries))
				{
					//Adding weapon to free entry
					AddWeapon(Weapon, Slot.Key, Entries);

					//Adding weapon icon
					Slot.Key->AddItemIcon(Weapon->GetWeaponIcon());

					return true;
				}
			}
		}
	}
	return false;
}

bool UInventoryComponent::CheckWeaponSlot(ACPP_WeaponBase* Weapon, UGearSlotWidgetBase* TargetSlot, int32 Index)
{
	if (!Weapon || !TargetSlot) return false;

	//Getting weapon size
	FIntPoint WeaponSize = Weapon->GetWeaponSize();

	//Converting entries to 2D
	FIntPoint TargetPosition = WeaponIndexToPosition(Index,TargetSlot);

	//Ensuring start index && size are valid
	if (!IsWeaponPositionValid(WeaponSize, TargetPosition, TargetSlot)) { return false; }

	//Looping area X in weapon slot
	for (int32 PosX = TargetPosition.X; PosX <= TargetPosition.X + WeaponSize.X - 1; PosX++)
	{
        //Looping area Y in weapon slot
		for (int32 PosY = TargetPosition.Y; PosY <= TargetPosition.Y + WeaponSize.Y - 1; PosY++)
		{
			//Converting position back to index
			int32 TargetIndex = WeaponPositionToIndex(FIntPoint(PosX, PosY),TargetSlot);

			//Checking if target index is occupied, if nullptr returned, target area is free
			if (!GetWeaponAtIndex(TargetIndex, TargetSlot)) { return true; }
		}
	}
	return false;
}

//Sets added weapons state after store
void UInventoryComponent::AddWeapon(ACPP_WeaponBase* Weapon, UGearSlotWidgetBase* TargetSlot, int32 Index)
{
	if (!Weapon || !TargetSlot) return;
	
	//Getting weapon size
	FIntPoint WeaponSize = Weapon->GetWeaponSize();

	//Converting target pos to 2D
	FIntPoint TargetPosition = WeaponIndexToPosition(Index,TargetSlot);

	for (int32 PosX = TargetPosition.X; PosX <= TargetPosition.X + WeaponSize.X - 1; PosX++)
	{
		for (int32 PosY = TargetPosition.Y; PosY <= TargetPosition.Y + WeaponSize.Y - 1; PosY++)
		{
			//Converting target position back to 1D
			int32 TargetIndex = WeaponPositionToIndex(FIntPoint(PosX, PosY), TargetSlot);

			//Adding weapon to target index
			TargetSlot->WeaponSlotSizeData.StoredWeapons[TargetIndex] = Weapon;
            //Setting weapon collection state
			Weapon->WeaponAttributes.bCollected = true;
		}
	}
}

ACPP_WeaponBase* UInventoryComponent::GetWeaponAtIndex(int32 Index, UGearSlotWidgetBase* TargetSlot) const
{
	//Checking if weapons slot area as valid indices
	if (TargetSlot->WeaponSlotSizeData.StoredWeapons.IsValidIndex(Index))
	{
		//Returning weapon at valid index
		return TargetSlot->WeaponSlotSizeData.StoredWeapons[Index];
	}

	//return nullptr if no valid indices found
	return nullptr;
}

void UInventoryComponent::RemoveWeapon(FWeaponSlotSizeData& WeaponData,class ACPP_WeaponBase* WeaponToRemove)
{
	if (!WeaponToRemove) return;
    
	//Looping all entrys in weapon slot
	for (int32 Entries = 0; Entries < WeaponData.StoredWeapons.Num(); Entries++)
	{
        //Checking if target weapon is found in entry
		if (WeaponData.StoredWeapons[Entries] == WeaponToRemove)
		{
			//Removing target weapon from stored weapons
			WeaponData.StoredWeapons[Entries] = nullptr;
	    }
	}
}

bool UInventoryComponent::IsWeaponPositionValid(FIntPoint WeaponSize, FIntPoint TargetPosition, class UGearSlotWidgetBase* TargetSlot)
{
	if (!TargetSlot) return false;

	//Ensuring target position is within slot size range
	if (TargetPosition.X < 0 || TargetPosition.Y < 0) return false;
	//Ensuring weapon size does not exceed slot size range
	if (TargetPosition.X + WeaponSize.X > TargetSlot->WeaponSlotSizeData.Width) return false;
	if (TargetPosition.Y + WeaponSize.Y > TargetSlot->WeaponSlotSizeData.Height) return false;

	return true;
}


bool UInventoryComponent::CheckStorageType(EWeaponTypes _WeaponType, EStorageType _StorageType)
{
	//Cmpr passed types
	return StorageTypeData.Contains(_WeaponType) && StorageTypeData[_WeaponType] == _StorageType;
}

FIntPoint UInventoryComponent::WeaponIndexToPosition(int32 Index, class UGearSlotWidgetBase* TargetSlot) const
{
	return FIntPoint(Index % TargetSlot->WeaponSlotSizeData.Width, Index / TargetSlot->WeaponSlotSizeData.Width);
}

int32 UInventoryComponent::WeaponPositionToIndex(FIntPoint Position, class UGearSlotWidgetBase* TargetSlot) const
{
	int32 Index = Position.X + Position.Y * TargetSlot->WeaponSlotSizeData.Width;
	return int32(Index);
}

