#pragma once

//Component imports
class USkeltalMeshComponent;
class UCameraComponent;
class UInventoryComponent;
class UCPP_EquipmentComponent;

//Other imports
class UInventoryComponent;
class UCPP_EquipmentComponent;

//Engine imports
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CPP_Survivor.generated.h"

//Handles all character animation montages
USTRUCT(BlueprintType)
struct FCharacterAnimMontages
{
	GENERATED_BODY()

	//Knife transition when pulled out
	UPROPERTY(EditAnywhere);
	UAnimMontage* _PullKnifeTransition;

	//Knife light attack montage
	UPROPERTY(EditAnywhere);
	UAnimMontage* _KnifeLightAttack;

	FCharacterAnimMontages() :
	_PullKnifeTransition(nullptr),_KnifeLightAttack(nullptr)
	{

	}
};


UCLASS()
class ZONEBREAK_API ACPP_Survivor : public ACharacter
{
	GENERATED_BODY()

private:
	ACPP_Survivor();

	              ///<Private character functions && components>
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Component", meta = (AllowPrivateAccess = true));
	USkeletalMeshComponent* SurvivorMesh;

	UPROPERTY(EditAnywhere, Category = "Component", meta = (AllowPrivateAccess = true));
	UCameraComponent* SurvivorCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = true));
	UCPP_EquipmentComponent* EquipmentComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component", meta = (AllowPrivateAccess = true));
	UInventoryComponent* InventoryComponent;

public:
           /// <Public character functions && components>

	//Animation montage data struct
	UPROPERTY(EditAnywhere, Category = "AnimationMontagesData");
	FCharacterAnimMontages CharacterAnimationMontages;

	                ///<Getter functions>
	//Returns equipment component across classes
    UCPP_EquipmentComponent* GetEquipmentComponent() const;
    
	//Returns inventory component across classes
	UInventoryComponent* GetInventoryComponent() const;

protected:
	             ///<Protected character functions && components>
	
		//Overlap detections functions
	UFUNCTION()
	void OnBeginOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool b_FromSweep, const FHitResult& SweepResult);

	//Allows overlap trigger events
	void SetUpOverlapEvents();



	void ToggleInventory();
	
	//Melee Binds
	void EquipMelee();
	void MeleeAttack();

	//Basic loco-motion functions
	void MoveForward(const float Value);
	void MoveRight(const float Value);
	void LookUp(const float Value);
	void LookRight(const float Value);

	//Engine override functions
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
