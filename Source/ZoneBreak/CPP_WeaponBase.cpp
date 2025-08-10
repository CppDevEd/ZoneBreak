//Engine imports
#include "CPP_WeaponBase.h"

//Component imports
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"

//Other imports
ACPP_WeaponBase::ACPP_WeaponBase()
{ 	
	PrimaryActorTick.bCanEverTick = false;
    
	//Setting up weapon mesh component
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(GetRootComponent());
 
	//Remving collision from weapon, to allow overlap events
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//Setting up collision sphere component
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionSphere->SetupAttachment(WeaponMesh);	
}

void ACPP_WeaponBase::BeginPlay()
{
	Super::BeginPlay();
}

void ACPP_WeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//Collectable interface function
void ACPP_WeaponBase::OnWeaponCollect(class ACPP_Survivor* _Instigator)
{
	if (!_Instigator) return;
}

EWeaponTypes& ACPP_WeaponBase::GetWeaponType(class ACPP_WeaponBase* WeaponToCheck)
{	
	//Getting weapon to checks struct type data
	 FWeaponTypeData& TypeData = WeaponToCheck->WeaponTypeData;
	 return TypeData.WeaponType;
}

FIntPoint ACPP_WeaponBase::GetWeaponSize() const
{
	return WeaponSize;
}

class UTexture2D* ACPP_WeaponBase::GetWeaponIcon() const
{
	return WeaponIcon;
}





