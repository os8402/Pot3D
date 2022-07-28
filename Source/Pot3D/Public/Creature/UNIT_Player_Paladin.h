#pragma once

#include "CoreMinimal.h"
#include "Creature/UNIT_Player.h"
#include "UNIT_Player_Paladin.generated.h"

UCLASS()
class POT3D_API AUNIT_Player_Paladin : public AUNIT_Player
{
	GENERATED_BODY()
	
public:
	
	AUNIT_Player_Paladin();
	virtual void UseActiveSKill(FName skillName) override;


};
