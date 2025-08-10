//Engine imports
#include "InventoryComponent.h"

//Component imports
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

//Other imports
#include "InventoryWidget.h"

#include "CPP_Survivor.h"

UInventoryComponent::UInventoryComponent()
{	
	PrimaryComponentTick.bCanEverTick = true;
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();	

	CreateMainInventory();
}

void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UInventoryComponent::CreateMainInventory()
{
	//Ensuring inventory reference has been set
	if (!InventoryWidgetClass) return;
    
	//Creating inventory widget
	InventoryWidget = CreateWidget(GetWorld(), InventoryWidgetClass);

	if (!InventoryWidget) return;

	//Getting player character
	PlayerCharacter = Cast<class ACPP_Survivor>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (!PlayerCharacter) return;

	//Getting player character controller
	CharacterController = Cast<class APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (!CharacterController) return;

	//Setting inventory widget owner
	InventoryWidget->SetOwningPlayer(CharacterController);
	
	//Setting default states
	InventoryWidget->AddToViewport(true);
	InventoryWidget->SetVisibility(ESlateVisibility::Collapsed);
}

void UInventoryComponent::ToggleMainInventory()
{
	if (InventoryWidget->GetVisibility() == ESlateVisibility::Collapsed)
	{
		//Setting visibility to visible
		InventoryWidget->SetVisibility(ESlateVisibility::Visible);
		//Setting character input mode
		CharacterController->SetInputMode(FInputModeGameAndUI());
		//Setting cursor visibility
		CharacterController->SetShowMouseCursor(true);
	}
	else
	{
		//Setting visibility to collapsed
		InventoryWidget->SetVisibility(ESlateVisibility::Collapsed);
		//Setting character input mode
		CharacterController->SetInputMode(FInputModeGameOnly());
		//Setting cursor visibility
		CharacterController->SetShowMouseCursor(false);
	}
}
