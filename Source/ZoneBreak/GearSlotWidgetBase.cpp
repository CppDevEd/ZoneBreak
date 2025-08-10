//Engine imports
#include "GearSlotWidgetBase.h"


void UGearSlotWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

    //Initializes class pointers to other classes
	GetClassReferences();
}

void UGearSlotWidgetBase::GetClassReferences()
{
	//Getting player character
	PlayerCharacter = Cast<class ACPP_Survivor>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!PlayerCharacter) return;

	if (!PlayerCharacter->GetInventoryComponent()) return;
	//Getting player character inventory component
	InventoryComp = PlayerCharacter->GetInventoryComponent();
}