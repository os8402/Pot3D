#include "UI/WG_ItemSlot.h"
#include "Item/OBJ_Item.h"
#include "UI/WG_Inventory.h"
#include <Components/Button.h>

void UWG_ItemSlot::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	if (_BTN_Slot->IsHovered() && _inventory.IsValid())
	{
		_inventory->SetItemTooltipHovered(_item);
	}
}

void UWG_ItemSlot::NativePreConstruct()
{
	Super::NativePreConstruct();

	RefreshUI();
}

void UWG_ItemSlot::RefreshUI()
{

}

void UWG_ItemSlot::SetItem(UOBJ_Item* item)
{
	_item = item;
	UTexture2D* newTexture = nullptr;

	if (item != nullptr)
	{
		//TODO : Texture Set

		newTexture = Cast<UTexture2D>(
			StaticLoadObject(UTexture2D::StaticClass(), nullptr, *item->GetTexturePath().ToString()));

		SetTextureIcon(newTexture);
	}

	RefreshUI();
}
