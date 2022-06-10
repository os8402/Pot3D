

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ACP_Equipment.generated.h"

class UOBJ_Item;
class AUNIT_Character;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class POT3D_API UACP_Equipment : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UACP_Equipment();

	class UAudioComponent* GetAudioComp() { return _Audio_Comp; }

	void SetOwner(AUNIT_Character* owner) { _currentOwner = owner; }

	void SetEquipItem(UOBJ_Item* item);

	virtual void SoundPlay(int32 index);


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

protected:

	UPROPERTY(VisibleAnywhere, Category = "Audio")
	class UAudioComponent* _Audio_Comp;

	UPROPERTY(VisibleAnywhere, Category = "Owner")
	AUNIT_Character* _currentOwner;

	////�ɷ�ġ ����

	UPROPERTY(VisibleAnywhere, Category = "Item")
	UOBJ_Item* _currentItem;
		
};
