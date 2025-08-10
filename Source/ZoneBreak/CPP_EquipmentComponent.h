#pragma once

///This class is desinged to keep track of all equipables in the world,
/// it will display functions to the reflection system to allow back-end driven
/// animation logic

//Engine imports
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CPP_EquipmentComponent.generated.h"


//Tracks what character currently has equiped || Add as needed
UENUM(BlueprintType)
enum class EEquipType : uint8
{
	None     UMETA(DisplayName = "None"),
	Knife    UMETA(DisplayName = Knife)
};

//Holds equipment functions
USTRUCT(BlueprintType)
struct FCharacterEquipStates
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere);
	EEquipType EquipType;

	//Holds pointer to current equiped item
	TObjectPtr<class AActor> CurrentItem;

	FCharacterEquipStates() :
	EquipType(EEquipType::None), CurrentItem(nullptr)
	{

	}
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ZONEBREAK_API UCPP_EquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UCPP_EquipmentComponent();

	    ///<Public equipment component components && functions>

	//Data structs && enums
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "EquipData");
	EEquipType EquipType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "EquipData");
	FCharacterEquipStates CharacterEquipStates;


	///<Exposes current equipment type for back-end driven animation logic>
	UFUNCTION(BlueprintCallable)
	bool CurrentEquipment(EEquipType Type) const;

	///<Equip functions>
	
	//Knife functions && components
	void EquipKnife();
	void GetKnifeClass(class ACPP_DefaultKnife* KnifeClass);
	//Points to knife class instance
	class ACPP_DefaultKnife* Knife;
protected:
	     /// <Protected equipment component functions && components>
	
	//Engine override functions
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
