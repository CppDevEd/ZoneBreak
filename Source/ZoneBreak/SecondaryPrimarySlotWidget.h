#pragma once

///This class is a child of UGearSlotWidgetBase, it is the second primary weapon
///slot found in the inventory, its storage type is rifles (this extendes to
/// shot-guns, lmg's, snipers etc.


//Engine imports
#include "CoreMinimal.h"
#include "GearSlotWidgetBase.h"
#include "SecondaryPrimarySlotWidget.generated.h"


UCLASS()
class ZONEBREAK_API USecondaryPrimarySlotWidget : public UGearSlotWidgetBase
{
	GENERATED_BODY()
	
private:
	    ///<Private Secondary primary slot widget functions && components>

	virtual void NativeConstruct() override;

	//Pointer to current weapon in slot
	class ACPP_WeaponBase* CurrentWeapon = nullptr;


	///<UI input event functions && components || Declare in children when needed, each child should handle their own drag, and drop events, as they each work with different object types>
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, class UDragDropOperation*& OutOperation) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	                     ///<Misc>
	//Engine function overrides
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
public:

};
