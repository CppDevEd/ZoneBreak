//Engine imports
#include "CPP_Survivor.h"

//Comonent imports
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

//Other imports
#include "CPP_WeaponBase.h"
#include "CPP_DefaultKnife.h"
#include "CPP_ICollectable.h"

//Custom character components
#include "CPP_EquipmentComponent.h"
#include "InventoryComponent.h"

ACPP_Survivor::ACPP_Survivor()
{
	PrimaryActorTick.bCanEverTick = false;

	//Setting up survivor mesh component
	SurvivorMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PlayerMesh"));
	SurvivorMesh->SetupAttachment(GetRootComponent());
    
	//Setting up survivor camera component
	SurvivorCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	SurvivorCamera->SetupAttachment(GetMesh(), FName("head"));
	SurvivorCamera->bUsePawnControlRotation = true;

	//Setting up inventory component
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));

	//Setting up equipment component
	EquipmentComponent = CreateDefaultSubobject<UCPP_EquipmentComponent>(TEXT("EquipmentComponent"));


    //Settin up overlap events
	SetUpOverlapEvents();
}

void ACPP_Survivor::BeginPlay()
{
	Super::BeginPlay();

}

void ACPP_Survivor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACPP_Survivor::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Event::Binds
	PlayerInputComponent->BindAction(FName("ToggleInventory"), IE_Pressed, this, &ACPP_Survivor::ToggleInventory);
	
	PlayerInputComponent->BindAction(FName("EquipMelee"), IE_Pressed, this, &ACPP_Survivor::EquipMelee);
	PlayerInputComponent->BindAction(FName("MeleeAttack"), IE_Pressed, this, &ACPP_Survivor::MeleeAttack);

	//Axis::Binds
	PlayerInputComponent->BindAxis(FName("MoveForward"), this, &ACPP_Survivor::MoveForward);
	PlayerInputComponent->BindAxis(FName("MoveRight"), this, &ACPP_Survivor::MoveRight);
	PlayerInputComponent->BindAxis(FName("LookUp"), this, &ACPP_Survivor::LookUp);
	PlayerInputComponent->BindAxis(FName("LookRight"), this, &ACPP_Survivor::LookRight);
}

                  ///<Getters && setters>
class UCPP_EquipmentComponent* ACPP_Survivor::GetEquipmentComponent() const
{
	if (!EquipmentComponent) return nullptr;
	return EquipmentComponent;
}
class UInventoryComponent* ACPP_Survivor::GetInventoryComponent() const
{
	if (!InventoryComponent) return nullptr;
	return InventoryComponent;
}

void ACPP_Survivor::OnBeginOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool b_FromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor) return;

	if (OtherActor->GetClass()->ImplementsInterface(UCPP_ICollectable::StaticClass()))
	{
		//Casting other actor to weapon base class
		class ACPP_WeaponBase* Weapon = Cast<class ACPP_WeaponBase>(OtherActor);
		if (!Weapon) return;
		//Calling on weapon collected
		Weapon->OnWeaponCollect(this);
	}
}

void ACPP_Survivor::SetUpOverlapEvents()
{
	//Binding overlap event delegate to capsule component
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ACPP_Survivor::OnBeginOverlap);
}

                  ///<Event binds>
void ACPP_Survivor::ToggleInventory()
{
	InventoryComponent->ToggleMainInventory();
}

void ACPP_Survivor::EquipMelee()
{
	//Equipping knife
	EquipmentComponent->EquipKnife();
}

void ACPP_Survivor::MeleeAttack() 
{
	//Checking if knife is equiped
	if (EquipmentComponent->EquipType == EEquipType::Knife)
	{
		EquipmentComponent->Knife->OnKnifeAttack();
    }
}

//Basic loco-motion functions
void ACPP_Survivor::MoveForward(const float Value)
{
	const FVector& Direction = FRotationMatrix(FRotator(0.0f, GetControlRotation().Yaw, 0.0f)).GetUnitAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void ACPP_Survivor::MoveRight(const float Value)
{
	const FVector& Direction = FRotationMatrix(FRotator(0.0f, GetControlRotation().Yaw, 0.0f)).GetUnitAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

void ACPP_Survivor::LookUp(const float Value)
{
	AddControllerPitchInput(Value);
}

void ACPP_Survivor::LookRight(const float Value)
{
	AddControllerYawInput(Value);
}