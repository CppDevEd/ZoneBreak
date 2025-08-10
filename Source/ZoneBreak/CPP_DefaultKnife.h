#pragma once

///This is the only melee weapon that will exist in the game as far as I know
///it will have no part in the UI, and will never be able to be dropped,
///therefore it will have no effect on space or weight, it is the starting knife
/// every player will start with, and is the less effective weapon in the game

//Comonent imports
class USkeletalMeshComponent;

//Engine imports
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_DefaultKnife.generated.h"


//Defines knifes transform data for attachment etc
USTRUCT(BlueprintType)
struct FDefaultKnifeTransformData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere);
	FTransform EquipTransform;

	FDefaultKnifeTransformData() :
	 EquipTransform()
	{

	}
};

//Defines knifes default damage etc
USTRUCT(BlueprintType)
struct FDefaultKnifeData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere);
	float Damage;

	UPROPERTY(EditAnywhere);
	bool bEquipped;

	FDefaultKnifeData() :
	Damage(), bEquipped(false)
	{

	}
};


UCLASS()
class ZONEBREAK_API ACPP_DefaultKnife : public AActor
{
	GENERATED_BODY()
	
	ACPP_DefaultKnife();

private:
	         ///<Private default knife functions && components>

	UPROPERTY(EditAnywhere, Category = "Component", meta = (AllowPrivateAccess = true));
	USkeletalMeshComponent* KnifeMesh;

	//Knife transform struct data
	UPROPERTY(EditAnywhere, Category = "KnifeData", meta = (AllowPrivateAccess = true));
	FDefaultKnifeTransformData DefaultKnifeTransformData;

	     /// <All character reference components>

	class ACPP_Survivor* PlayerCharacter;
	class UCPP_EquipmentComponent* EquipmentComp;

	class USkeletalMeshComponent* PlayerMesh;
	class UAnimInstance* PlayerAnimInstance;

	//Initializes references
	void InitComponents();
    


	//Attaches knife to character at begin play
	void AttachToPlayer(class ACPP_DefaultKnife* Knife);
public:
            /// <Public default knife functions && components>
	void EquipKnife(class ACPP_DefaultKnife* KnifeToAdd);
	void UnEquipKnife(class ACPP_DefaultKnife* KnifeToRemove);
	
	//Plays the pull-out knife animation montage on equip
	void PlayTransitionMontage(class ACPP_Survivor* Character);
	//Plays attach montage
	void OnKnifeAttack();

	//Public knife properties, damage etc
	UPROPERTY(EditAnywhere, Category = "KnifeData");
	FDefaultKnifeData DefaultKnifeData;

protected:
	        ///<Protected default knife functions && components>

	//Engine override functions
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
