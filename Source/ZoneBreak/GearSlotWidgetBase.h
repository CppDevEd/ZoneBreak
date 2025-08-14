#pragma once

///All weapon && gear slots attached to the main inventory component are
///derived from this class

//Component imports
#include "Components/CanvasPanel.h"
#include "Components/Border.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/PanelSlot.h"
#include "Components/Image.h"
#include "Components/BrushComponent.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/DragDropOperation.h"

#include "Kismet/GameplayStatics.h"

//Other components
class ACPP_Survivor;
class UInventoryComponent;
class UCPP_EquipmentComponent;

//Engine imports
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GearSlotWidgetBase.generated.h"


//Each slot will have a storage type
UENUM(BlueprintType)
enum class EStorageType : uint8
{
	/// <summary>
	/// Change the order later, as the comparision for the slot names
	/// are static_cast, any more checks between would fail later
	/// </summary>

	SideArm UMETA(DisplayName = "SideArmSlot"),
	Rifle UMETA(DisplayName = "RifleSlot"),
	Helmet UMETA(DisplayName = "HelmetSlot"),
	PlateCarrier UMETA(DisplayNam = "PlateCarrierSlot")
	//etc...
};

//Each slot will set its own size && Data type to store
USTRUCT(BlueprintType)
struct FWeaponSlotSizeData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere);
	int32 Width;

	UPROPERTY(EditAnywhere);
	int32 Height;

	UPROPERTY(EditAnywhere);
	float CellSize;

	//This array represents the slot space in memory
	UPROPERTY(VisibleAnywhere);
	TArray<class ACPP_WeaponBase*> StoredWeapons;

	void SetSlotSize()
	{
		StoredWeapons.SetNum(Width * Height);
	}

	FWeaponSlotSizeData() :
	Width(), Height(), CellSize(),StoredWeapons()
	{

	}
};


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

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI");
	UImage* SlotIcon; 

	//Added item image icon
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI");
	UImage* CollectedItemIcon;

	//Inits class references on construct
	void SetClassReferences();

	//Other class references
	ACPP_Survivor* PlayerCharacter;
	UInventoryComponent* InventoryComp;
	UCPP_EquipmentComponent* EquipmentComp;

	          ///<UI input helper functions>

	//Retruns a duplicate image pointer for passed image, used for performing visual drag operations
	UImage* CreateVisualDragImage(UImage* ImageToDuplicate);

	              ///<Misc>
	//Engine override function
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
public:
	     ///<Public access components>
	
	//Addes generic item icon when called
	void AddItemIcon(class UTexture2D* IconToAdd);
	
	//Adds slot icon back to render on call
	void AddSlotIcon();


	        /// <Getters>
	EStorageType GetStorageType() const;

           ///<Data structs>
	UPROPERTY(EditAnywhere, Category = "SlotData");
	FWeaponSlotSizeData WeaponSlotSizeData;

	UPROPERTY(EditAnywhere, Category = "StorageTypeData");
	EStorageType StorageType;
};
