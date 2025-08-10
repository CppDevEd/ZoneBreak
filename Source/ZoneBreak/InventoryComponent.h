#pragma once

//Component imports
class UUserWidget;
class APlayerController;

//Other imports
class ACPP_Survivor;

//Engine imports
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ZONEBREAK_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UInventoryComponent();

	//Creates default inventory widget at begin play
	void CreateMainInventory();

	//Holds reference to inventory widget class,set in editor
	UPROPERTY(EditAnywhere, Category = "UI Data", meta = (AllowPrivateAccess = true));
	TSubclassOf<UUserWidget> InventoryWidgetClass;
	//Local pointer to inventory widget
	UUserWidget* InventoryWidget;
	 
	//Character reference, used for setting owner etc
	ACPP_Survivor* PlayerCharacter;

	//Player characters controller
	APlayerController* CharacterController;

public:
	
	//Displays main inventory, called in player character class
	void ToggleMainInventory();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
