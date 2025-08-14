//Engine imports
#include "GearSlotWidgetBase.h"

//Other imports
#include "CPP_WeaponBase.h"

#include "CPP_Survivor.h"
#include "InventoryComponent.h"

void UGearSlotWidgetBase::NativeConstruct()
{
    Super::NativeConstruct();

	//Sets class component references on construct
	SetClassReferences();
}

void UGearSlotWidgetBase::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UGearSlotWidgetBase::SetClassReferences()
{
	//Getting player character
	PlayerCharacter = Cast<class ACPP_Survivor>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	
	if (!PlayerCharacter) return;

	//Getting player character inventory component
	if (!PlayerCharacter->GetInventoryComponent()) return;

	InventoryComp = PlayerCharacter->GetInventoryComponent();

	if (!InventoryComp) return;

	//Getting player character equipment component
	if (!PlayerCharacter->GetEquipmentComponent()) return;

	EquipmentComp = PlayerCharacter->GetEquipmentComponent();
}

EStorageType UGearSlotWidgetBase::GetStorageType() const
{
	return (StorageType);
}

//Adds icon when called
void UGearSlotWidgetBase::AddItemIcon(class UTexture2D* IconToAdd)
{
	if (!IconToAdd) return;

	if (!CollectedItemIcon) return;
    
	//Adding passed texture to image
	CollectedItemIcon->SetBrushFromTexture(IconToAdd);

	//Checking if collected item is currently collapsed
	if (CollectedItemIcon->GetVisibility() == ESlateVisibility::Collapsed)
	{
		//Setting visible
		CollectedItemIcon->SetVisibility(ESlateVisibility::Visible);
	}
	
	if (!SlotIcon) return;

	//Checking current slot icon state
	if (SlotIcon->GetVisibility() == ESlateVisibility::Visible)
	{
		//Removing place holder from inventory visibility
		SlotIcon->SetVisibility(ESlateVisibility::Collapsed);
	}
}

//Adds slot icon back to widget render
void UGearSlotWidgetBase::AddSlotIcon()
{
	if (!SlotIcon) return;

	//Ensuring slot icon is not already being rendered
	if (SlotIcon->GetVisibility() == ESlateVisibility::Collapsed)
	{
		//Adding slot icon back into widget render
		SlotIcon->SetVisibility(ESlateVisibility::Visible);
	}
}

class UImage* UGearSlotWidgetBase::CreateVisualDragImage(class UImage* ImageToDuplicate)
{
	if (!ImageToDuplicate) return nullptr;

	//Creating duplicate of passed image
	class UImage* DragIcon = DuplicateObject<class UImage>(ImageToDuplicate, this);
	
	//Duplicating drag image properties
	DragIcon->SetBrush(ImageToDuplicate->GetBrush());
	//Adding drag icon to render
	DragIcon->SetVisibility(ESlateVisibility::Visible);

	//Returning drag icon
	return DragIcon;
}
