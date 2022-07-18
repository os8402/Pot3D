#pragma once

#include "CoreMinimal.h"
#include "UI/WG_Slot.h"
#include "WG_ItemSlot.generated.h"


UCLASS()
class POT3D_API UWG_ItemSlot : public UWG_Slot
{
	GENERATED_BODY()

public:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void NativePreConstruct() override;
	virtual void RefreshUI() override;

	void SetItem(UOBJ_Item* item);
	UOBJ_Item* GetItem() { return _item; }

	void SetInventory(UWG_Inventory* inventory) { _inventory = inventory; }


protected:


	UPROPERTY()
	UOBJ_Item* _item;

	TWeakObjectPtr<UWG_Inventory> _inventory;
	
};
