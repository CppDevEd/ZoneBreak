#pragma once

//Engine imports
#include "CoreMinimal.h"
#include "GearSlotWidgetBase.h"
#include "PrimaryWeaponSlotWidget.generated.h"


USTRUCT(BlueprintType)
struct FPrimaryWeaponSlotData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere);
	int32 Columns;

	UPROPERTY(EditAnywhere);
	int32 Rows;

	UPROPERTY(EditAnywhere);
	float TileSize;

	FPrimaryWeaponSlotData() :
		Columns(), Rows(), TileSize()
	{

	}
};

UCLASS()
class ZONEBREAK_API UPrimaryWeaponSlotWidget : public UGearSlotWidgetBase
{
	GENERATED_BODY()
	
private:
	    ///<Private PrimaryWeaponSlotWidget components && functions>
	virtual void NativeConstruct() override;

public:
	    ///<Public PrimaryWeaponSlotWidget components && functions>

	//Data structs
	//Inventory data structs
	UPROPERTY(EditAnywhere, Category = "WeaponSlotData");
	FPrimaryWeaponSlotData PrimaryWeaponSlotData;
};
