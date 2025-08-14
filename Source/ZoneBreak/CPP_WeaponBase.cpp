//Engine imports
#include "CPP_WeaponBase.h"

//Component imports
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"

#include "Kismet/GameplayStatics.h"

//Other imports
#include "CPP_Survivor.h"


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

//Attaches weapon to character, and removes it from render
void ACPP_WeaponBase::AddWeaponToCharacter(class ACPP_WeaponBase* WeaponToAdd, class ACPP_Survivor* PlayerCharacter)
{
	if (!WeaponToAdd) return;

	//Getting weapon to add attributes data
	FWeaponAttributes& WeaponAtts = WeaponToAdd->WeaponAttributes;

	//Checking if has been added to character inventory
	if (WeaponAtts.bCollected)
	{
		//remove log later
		if (!PlayerCharacter) { GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Character nullptr")); return; }
		
		//Attaching to item socket
		WeaponToAdd->AttachToComponent(PlayerCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("ItemSocket.L"));
		//Setting transform
		WeaponToAdd->SetActorRelativeTransform(WeaponAtts.EquipTransform);

		//Removing weapon from render
		WeaponToAdd->WeaponMesh->SetVisibility(false);

		//Adding pointer to current collected weapon
		WeaponToAdd->CollectedWeaponData.CollectedWeapons.Add(WeaponToAdd);
	}
}

                   ///<Equip functions>

void ACPP_WeaponBase::EquipWeapon(class ACPP_WeaponBase* Weapon)
{
	if (!Weapon) return;

	//Getting passed weapon attributes
	FWeaponAttributes& WeaponAtts = Weapon->WeaponAttributes;
	
	//Adding weapon to render
	Weapon->WeaponMesh->SetVisibility(true);

	//Setting weapon state
	WeaponAtts.bEquipped = true;
}

void ACPP_WeaponBase::UnEquipWeapon(class ACPP_WeaponBase* Weapon)
{
	if (!Weapon) return;

	//Getting passed weapon attributes
	FWeaponAttributes& WeaponAtts = Weapon->WeaponAttributes;

	//Removing weapon from render
	Weapon->WeaponMesh->SetVisibility(false);

	//Setting weapon state
	WeaponAtts.bEquipped = false;
}
                 ///<Getter && setter functions>
EWeaponTypes& ACPP_WeaponBase::GetWeaponType(class ACPP_WeaponBase* WeaponToCheck)
{	
	 //Getting weapon to checks struct type data
	FCollectedWeaponData& TypeData = WeaponToCheck->CollectedWeaponData;
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

void ACPP_WeaponBase::SetNewWeaponUIData(class ACPP_WeaponBase* NewWeapon, FIntPoint NewSize, class UTexture2D* NewIcon)
{
	if (!NewWeapon) return;

	//Setting new weapon size
	NewWeapon->WeaponSize = NewSize;

	//Setting icon
	NewWeapon->WeaponIcon = NewIcon;
}





