

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ACP_Equipment.generated.h"

class UOBJ_Item;
class AUNIT_Player;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class POT3D_API UACP_Equipment : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UACP_Equipment();

	void SetOwner(AUNIT_Player* owner) { _currentOwner = owner; }
	void EquipItem(UOBJ_Item* item);
	void UnEquipItem();

	UOBJ_Item* GetItem() {return _currentItem;}

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

protected:

	UPROPERTY(VisibleAnywhere, Category = "Owner")
	AUNIT_Player* _currentOwner;

	////능력치 관련

	UPROPERTY(VisibleAnywhere, Category = "Item")
	UOBJ_Item* _currentItem;
		
};
