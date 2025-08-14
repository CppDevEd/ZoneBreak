#pragma once

///Main widget which surves as a container for all other UI widgets with regards
///to the inventory, such as weapon slots, character inventory etc.


//Component imports
class UCanvasPanel;
class UBorder;
class UBackgroundBlur;
class UPanelWidget;

//Other imports
class ACPP_Survivor;
class UInventoryComponent;

//Engine imports
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"


UCLASS()
class ZONEBREAK_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:
	       ///<Private inventory widget components && functions>
	virtual void NativeConstruct() override;
    
	//Sets class references on construct
	void SetClassReferences();

	//Global class references
	ACPP_Survivor* PlayerCharacter;
	UInventoryComponent* InventoryComp;

	//Used to get widget root
	UPanelWidget* PanelWidget;

public:
	      ///<Public inventory widget components && functions>

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI");
	UCanvasPanel* Canvas;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI");
	UBorder* Border;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI");
	UBackgroundBlur* Blur;


	                 ///<Getters>
	//Returns widget root
	class UPanelWidget* InventoryCache();

	  ///<Misc helper components && references && functions>
	
	//Points to the latest drag and dropped spawned weapon
	class ACPP_WeaponBase* SpawnedWeapon;



protected:
	      ///<Protected inventory widget components && functions>

	             ///<UI input event function overrides>
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
    
	//Spawns instances of drpped items
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, class UDragDropOperation* InOperation) override;
};
