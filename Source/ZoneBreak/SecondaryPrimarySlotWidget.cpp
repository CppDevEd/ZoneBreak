//Engine imports
#include "SecondaryPrimarySlotWidget.h"

//Other imports
#include "InventoryComponent.h"


void USecondaryPrimarySlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//Setting slot size
	WeaponSlotSizeData.SetSlotSize();
}


void USecondaryPrimarySlotWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}


                    ///<UI input event functions>
void USecondaryPrimarySlotWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, class UDragDropOperation*& OutOperation)
{
	//Creating new drag drop operation in memory
	class UDragDropOperation* DragDropOperation = NewObject<class UDragDropOperation>();

	if (!DragDropOperation) return;

	//Performing visual drag operation on item icon
	DragDropOperation->DefaultDragVisual = CreateVisualDragImage(CollectedItemIcon);

	//Removing static image from slot render
	CollectedItemIcon->SetVisibility(ESlateVisibility::Collapsed);

	//Getting weapon pointer from primary slot
	for (class ACPP_WeaponBase* FoundWeapon : WeaponSlotSizeData.StoredWeapons)
	{
		//Should exit early before adding nullptr to pay-load
		if (!FoundWeapon) return;

		//Adding dragged weapon to pay load
		DragDropOperation->Payload = FoundWeapon;

		//Holds pointer to current weapon in slot
		CurrentWeapon = FoundWeapon;
	}
	//Removing weapon from weapon slot when being dragged
	InventoryComp->RemoveWeapon(WeaponSlotSizeData, CurrentWeapon);

	//Adding slot icon back into render
	AddSlotIcon();

	//Setting OutOperation
	OutOperation = DragDropOperation;
}

FReply USecondaryPrimarySlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	return FReply::Handled().DetectDrag(TakeWidget(), EKeys::LeftMouseButton);
}



