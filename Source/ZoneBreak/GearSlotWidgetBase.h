#pragma once

///All weapon && gear slots attached to the main inventory component are
///derived from this class

//Component imports
#include "Components/CanvasPanel.h"
#include "Components/Border.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/PanelSlot.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Kismet/GameplayStatics.h"


//Other imports
#include "CPP_Survivor.h"
#include "InventoryComponent.h"


//Engine imports
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GearSlotWidgetBase.generated.h"


UCLASS()
class ZONEBREAK_API UGearSlotWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	       ///<Protected gear slot widget base components && functions>      
	virtual void NativeConstruct() override;
     
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI");
	UCanvasPanel* Canvas;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI");
	UBorder* Border;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI");
	UCanvasPanel* BorderCanvas;

	//Gets class pointers for child classes to use
	void GetClassReferences();

	//Character && Character component pointers
	ACPP_Survivor* PlayerCharacter;
	UInventoryComponent* InventoryComp;
};
