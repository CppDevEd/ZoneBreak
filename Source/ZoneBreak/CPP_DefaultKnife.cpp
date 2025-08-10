//Engine imports
#include "CPP_DefaultKnife.h"

//Comonent imports
#include "Kismet/GameplayStatics.h"

//Other imports
#include "CPP_Survivor.h"
#include "CPP_EquipmentComponent.h"


/// <summary>
/// Ensure to add actual damage effects and such to this implementation later
/// by way of a ray-cast, and hit result checks
/// </summary>

ACPP_DefaultKnife::ACPP_DefaultKnife()
{
	PrimaryActorTick.bCanEverTick = false;

	//Setting up knife mesh component
	KnifeMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("KnifeMesh"));
	KnifeMesh->SetupAttachment(GetRootComponent());

	//Removing collision from knife mesh to prevent issues with character collision
	KnifeMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ACPP_DefaultKnife::BeginPlay()
{
	Super::BeginPlay();

	//Initializes class references
	InitComponents();
}

void ACPP_DefaultKnife::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACPP_DefaultKnife::InitComponents()
{
	//Getting player character
	PlayerCharacter = Cast<class ACPP_Survivor>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
    
	if (!PlayerCharacter) return;

	//Getting  player character equipment component
	if (!PlayerCharacter->GetEquipmentComponent()) return;
	EquipmentComp = PlayerCharacter->GetEquipmentComponent();
	//Passes self to equipment component class
	EquipmentComp->GetKnifeClass(this);
	

	//Added here to ensure that player character is valid, before attempting to attach to its component
	AttachToPlayer(this);
}


void ACPP_DefaultKnife::AttachToPlayer(class ACPP_DefaultKnife* Knife)
{
	if (!Knife) return;
     
	//Setting knife default visibility state
	Knife->KnifeMesh->SetVisibility(false);

	//Getting  transform data of passed knife
	FDefaultKnifeTransformData& KnifeTransformData = Knife->DefaultKnifeTransformData;

	//Attaching knife to player character hand socket
	Knife->AttachToComponent(PlayerCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("ItemSocket.R"));
	//Setting knife transform
	Knife->SetActorRelativeTransform(KnifeTransformData.EquipTransform);
}

void ACPP_DefaultKnife::EquipKnife(class ACPP_DefaultKnife* KnifeToAdd)
{
	if (!PlayerCharacter || !KnifeToAdd) return;

	//Adding knife to render
	KnifeToAdd->KnifeMesh->SetVisibility(true);

	//Getting knife state data struct
	FDefaultKnifeData& KnifeData = KnifeToAdd->DefaultKnifeData;

	//Setting knife equip state
	KnifeData.bEquipped = true;

	//Playing equip knife transition
	PlayTransitionMontage(PlayerCharacter);
}

void ACPP_DefaultKnife::UnEquipKnife(class ACPP_DefaultKnife* KnifeToRemove)
{
	if (!KnifeToRemove) return;

	//Getting knife state data struct
	FDefaultKnifeData& KnifeData = KnifeToRemove->DefaultKnifeData;

	//Removing knife from render and setting its equip state
	KnifeToRemove->KnifeMesh->SetVisibility(false);
	KnifeData.bEquipped = false;
}

void ACPP_DefaultKnife::PlayTransitionMontage(class ACPP_Survivor* Character)
{
	if (!Character) return;

	//Getting player character animation montages struct
	const FCharacterAnimMontages& CharacterMontages = Character->CharacterAnimationMontages;

	//Holds pointer to player character skeletal mesh
	 PlayerMesh = Character->GetMesh();

	if (!PlayerMesh) return;

	//Getting current player animation instance
	PlayerAnimInstance = PlayerMesh->GetAnimInstance();

	if (!PlayerAnimInstance) return;

	//Ensuring target montage is valid
	if (!CharacterMontages._PullKnifeTransition) return;

	//Playing transition montage
	PlayerAnimInstance->Montage_Play(CharacterMontages._PullKnifeTransition);
}

void ACPP_DefaultKnife::OnKnifeAttack()
{
	if (!PlayerCharacter || !PlayerAnimInstance) return;

	//Getting player character montages
	const FCharacterAnimMontages& CharacterMontages = PlayerCharacter->CharacterAnimationMontages;

	//Ensuring target montage is valid
	if (!CharacterMontages._KnifeLightAttack) return;

	//Playing attack montage
	PlayerAnimInstance->Montage_Play(CharacterMontages._KnifeLightAttack);
}