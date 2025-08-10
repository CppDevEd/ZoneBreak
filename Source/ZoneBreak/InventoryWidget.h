#pragma once

///Main widget which surves as a container for all other UI widgets with regards
///to the inventory, such as weapon slots, character inventory etc.


//Component imports
class UCanvasPanel;
class UBorder;
class UBackgroundBlur;

//Engine imports
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"


UCLASS()
class ZONEBREAK_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:
	       ///<Private inventory widget components && functions>
	virtual void NativeConstruct() override;

public:
	      ///<Public inventory widget components && functions>

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI");
	UCanvasPanel* Canvas;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI");
	UBorder* Border;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI");
	UBackgroundBlur* Blur;
};
