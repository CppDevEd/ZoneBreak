#pragma once

///This is a base class for all gun weapons which can be found
///in game

//Component imports
#include "Kismet/GameplayStatics.h"

class USkeletalMeshComponent;
class USphereComponent;
class UMaterialInterface;

//Other imports
#include "CPP_ICollectable.h"
#include "CPP_Survivor.h"

//Engine imports
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_WeaponBase.generated.h"


//Handles weapon type data such as rifle, pistol etc.
UENUM(BlueprintType)
enum class EWeaponTypes : uint8
{
	None   UMETA(DisplayName = "None"),

	Rifle  UMETA(DisplayName = "Rifle"),

	Pistol UMETA(DisplayName = "Pistol")
};

//Defines a weaposn carry type
USTRUCT(BlueprintType)
struct FWeaponTypeData
{
	GENERATED_BODY()

	//Empty instance of EWeaponType used for type check
	UPROPERTY(EditAnywhere);
	EWeaponTypes WeaponType;

	//Direct pointer to the current equiped weapon
	UPROPERTY();
	TObjectPtr<class AActor> EquipedWeapon;

	FWeaponTypeData() :
	WeaponType(EWeaponTypes::None), EquipedWeapon(nullptr)
	{

	}
};

UCLASS()
class ZONEBREAK_API ACPP_WeaponBase : public AActor, public ICPP_ICollectable
{
	GENERATED_BODY()
	
protected:	
	         ///<Protected weapon base functions && components>
	ACPP_WeaponBase();

	//Mesh related weapon components
	UPROPERTY(EditAnywhere, Category = "Component");
	USkeletalMeshComponent* WeaponMesh; 

	UPROPERTY(EditAnywhere, Category = "Component");
	USphereComponent* CollisionSphere;

	//Universal size of each weapon for inventory space
	UPROPERTY(EditAnywhere, Category = "WeaponData");
	FIntPoint WeaponSize; ///<In the case the weapon slot size is changed, this must be changed to match, or else the inventory code will not work properly>

	//Stores weapons inventory icons
	UPROPERTY(EditAnywhere, Category = "WeaponData");
	UTexture2D* WeaponIcon;

public:
	    ///<Public weapon base components && functions>
	
		//Getters && setters
	FIntPoint GetWeaponSize() const;
	class UTexture2D* GetWeaponIcon() const;

	///<Weapon data structures && enum's>
	//Stores weapon type which is set in the editor
	UPROPERTY(EditAnywhere,Category = "WeaponData");
	FWeaponTypeData WeaponTypeData;

	//Returns latest collect weapon type
	EWeaponTypes& GetWeaponType(class ACPP_WeaponBase* WeaponToCheck);

	//Other function overrides
	virtual void OnWeaponCollect(class ACPP_Survivor* _Instigator) override;
private:
	//Engine overrides
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
