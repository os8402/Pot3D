#include "UI/WG_Slot.h"
#include "Item/OBJ_Item.h"
#include "UI/WG_Inventory.h"
#include <Components/Button.h>


void UWG_Slot::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UWG_Slot::NativePreConstruct()
{
	Super::NativePreConstruct();

	RefreshUI();
}

void UWG_Slot::RefreshUI()
{
	
}
