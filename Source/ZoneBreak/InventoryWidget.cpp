//Engine imports
#include "InventoryWidget.h"

//Component imports
#include "Components/PanelWidget.h"
#include "Blueprint/DragDropOperation.h"

#include "Kismet/GameplayStatics.h"


//Other imports
#include "CPP_Survivor.h"
#include "CPP_WeaponBase.h"

#include "InventoryComponent.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//Setting class references at construct
	SetClassReferences();
}

void UInventoryWidget::SetClassReferences()
{
	//Getting player character
	PlayerCharacter = Cast<class ACPP_Survivor>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	
	if (!PlayerCharacter) return;

	//Geting player character inventory component
	if (!PlayerCharacter->GetInventoryComponent()) return;

	InventoryComp = PlayerCharacter->GetInventoryComponent();

	if (!InventoryComp) return;

	//Passing cached data to inventory component || Called here to ensure that all components are valid first
	InventoryComp->CachedInventoryData();
}


//Returns root widget
class UPanelWidget* UInventoryWidget::InventoryCache()
{
	//Points to inventory widgets root
	PanelWidget = Cast<class UPanelWidget>(this->GetRootWidget());

	if (!PanelWidget) return nullptr;

	return PanelWidget;
}

                   ///<UI Input event functions>
bool UInventoryWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, class UDragDropOperation* InOperation)
{
	//Ensuring pay-load is valid
	if (!InOperation->Payload) return false;

	//Checking if weapon has been dropped
	class ACPP_WeaponBase* DroppedWeapon = Cast<class ACPP_WeaponBase>(InOperation->Payload);

	if (!DroppedWeapon) return false;

	//Setting dropped weapons spawn parameters
	if (!PlayerCharacter) return false;

	//Setting spawn location
	FVector WeaponSpawnLocation = PlayerCharacter->GetActorLocation() + PlayerCharacter->GetActorForwardVector() * DroppedWeapon->WeaponSpawnOffset;
    //Setting spawn location
	FRotator WeaponSpawnRotation = PlayerCharacter->GetActorRotation();

	//spawn params
	FActorSpawnParameters WeaponSpawnParams;
	WeaponSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	//Spawning weapon
	SpawnedWeapon = GetWorld()->SpawnActor<class ACPP_WeaponBase>(InOperation->Payload->GetClass(), WeaponSpawnLocation, WeaponSpawnRotation, WeaponSpawnParams);

	if (!SpawnedWeapon) return false;

	//Setting spawned weapon UI data for next pick-up
	SpawnedWeapon->SetNewWeaponUIData(SpawnedWeapon, DroppedWeapon->GetWeaponSize(), DroppedWeapon->GetWeaponIcon());
	return true;
}

FReply UInventoryWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	return FReply::Handled();
}

