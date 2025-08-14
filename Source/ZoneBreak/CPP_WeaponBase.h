#pragma once

///This is a base class for all gun weapons which can be found
///in game


//Component imports
class USkeletalMeshComponent;
class USphereComponent;
class UMaterialInterface;

//Other imports
#include "CPP_ICollectable.h"
class ACPP_Survivor;

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

//Defines a weapons carry type
USTRUCT(BlueprintType)
struct FCollectedWeaponData
{
	GENERATED_BODY()

	//Empty instance of EWeaponType used for type check
	UPROPERTY(EditAnywhere);
	EWeaponTypes WeaponType;

	//Direct pointers to the current collected weapons
	UPROPERTY();
	TArray<TObjectPtr<class AActor>> CollectedWeapons;

	FCollectedWeaponData() :
	WeaponType(EWeaponTypes::None), CollectedWeapons()
	{

	}
};

//Defines weapon attributes, equipped, transform, ammo type, etc.
USTRUCT(BlueprintType)
struct FWeaponAttributes
{
	GENERATED_BODY()

	//Set true when added into inventory
	UPROPERTY(EditAnywhere);
	bool bCollected;

	UPROPERTY(EditAnywhere);
	bool bEquipped;

	UPROPERTY(EditAnywhere);
	FTransform EquipTransform;

	FWeaponAttributes() :
		bCollected(false),bEquipped(false), EquipTransform()
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
	FIntPoint WeaponSize; ///<In the case the weapon slot size is changed, this must be changed to match, or else the inventory logic will not work properly>

	//Stores weapons inventory icons
	UPROPERTY(EditAnywhere, Category = "WeaponData");
	UTexture2D* WeaponIcon;

	//Attaches weapon to character, and removes it from render when picked-up
	void AddWeaponToCharacter(class ACPP_WeaponBase* WeaponToAdd, class ACPP_Survivor* PlayerCharacter);

public:
	 ///<Public weapon base components && functions>

	             /// <Equip weapon functions>

	void EquipWeapon(class ACPP_WeaponBase* Weapon);
	void UnEquipWeapon(class ACPP_WeaponBase* Weapon);

		//Getters && setters
	FIntPoint GetWeaponSize() const;
	class UTexture2D* GetWeaponIcon() const;

	//Sets newley spawned weapons, its class type UI data
	void SetNewWeaponUIData(class ACPP_WeaponBase* NewWeapon,FIntPoint NewSize, class UTexture2D* NewIcon);


	///<Weapon data structures && enum's>
	//Stores weapon type which is set in the editor
	UPROPERTY(EditAnywhere,Category = "WeaponData");
	FCollectedWeaponData CollectedWeaponData;

	UPROPERTY(EditAnywhere, Category = "WeaponData");
	FWeaponAttributes WeaponAttributes;

	//Dictates how far forward the weapon will spawn when dropped from inventory widgets
	UPROPERTY(EditAnywhere, Category = "SpawnData");
	float WeaponSpawnOffset = 200.0f;

	//Returns latest collect weapon type
	EWeaponTypes& GetWeaponType(class ACPP_WeaponBase* WeaponToCheck);
    
	//Other function overrides
	virtual void OnWeaponCollect(class ACPP_Survivor* _Instigator) override;
private:
	//Engine overrides
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
