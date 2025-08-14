#pragma once

//Component imports
class UUserWidget;
class APlayerController;

//Other imports
class ACPP_Survivor;

#include "CPP_WeaponBase.h"
#include "GearSlotWidgetBase.h"

//Engine imports
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ZONEBREAK_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UInventoryComponent();

	//Creates default inventory widget at begin play
	void CreateMainInventory();

	   ///<Main inventory container components>

	//Holds reference to inventory widget class,set in editor
	UPROPERTY(EditAnywhere, Category = "UI Data", meta = (AllowPrivateAccess = true));
	TSubclassOf<UUserWidget> InventoryWidgetClass;
	
	//Local pointer to inventory widget
	UUserWidget* InventoryWidget;
	 
	     ///<Other class references>
	//Character reference, used for setting owner etc
	ACPP_Survivor* PlayerCharacter;
	
	//Player characters controller
	APlayerController* CharacterController;
public:
	                ///<Inventory logic functions>
       
   ///<Weapon related inventory functions (not universal to other items of type, collectable base, gear base etc.>	

	//Called for every weapon overlapped
	bool WeaponOverlapped(class ACPP_WeaponBase* Weapon);

	//Checks if target slot is occupied
	bool CheckWeaponSlot(class ACPP_WeaponBase* Weapon, class UGearSlotWidgetBase* TargetSlot, int32 Index);
   
	//Checks if weapon size, && target position is valid
	bool IsWeaponPositionValid(FIntPoint WeaponSize, FIntPoint TargetPosition,class UGearSlotWidgetBase* TargetSlot);
    
	//Addes weapon at target index
	void AddWeapon(class ACPP_WeaponBase* Weapon, class UGearSlotWidgetBase* TargetSlot, int32 Index);

	//Removes weapon from inventory
	void RemoveWeapon(FWeaponSlotSizeData& WeaponData,class ACPP_WeaponBase* WeaponToRemove);

	//Returns weapon at index
	class ACPP_WeaponBase* GetWeaponAtIndex(int32 Index, class UGearSlotWidgetBase* TargetSlot) const;
    
	//cmpr weapon type && storage type, returns true if they match
	bool CheckStorageType(EWeaponTypes _WeaponType, EStorageType _StorageType);


	//Weapon array conversion functions
	FIntPoint WeaponIndexToPosition(int32 Index,class UGearSlotWidgetBase* TargetSlot) const;

	int32 WeaponPositionToIndex(FIntPoint Position,class UGearSlotWidgetBase* TargetSlot) const;


	            ///<Data functions && structures>

	//Holds all gear slot widget class children in main inventory
	UPROPERTY(VisibleAnywhere, Category = "GearSlotDat");
	TMap<UGearSlotWidgetBase*, EStorageType> GearSlotData;

	//Used for cmpr weapon type && gear slot type,simply add in editor
	UPROPERTY(EditAnywhere, Category = "GearSlotData");
	TMap<EWeaponTypes, EStorageType> StorageTypeData;

	//Gets all child components of type gear slots in inventory widget
	void CachedInventoryData();

	                      ///<Misc>
	//Displays main inventory, called in player character class
	void ToggleMainInventory();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
