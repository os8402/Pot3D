#pragma once

#include "CoreMinimal.h"
#include "Skill/ACP_SKillInfo.h"
#include "ACP_SKillInfo_Paladin.generated.h"

class AUNIT_Character;

UCLASS()
class POT3D_API UACP_SKillInfo_Paladin : public UACP_SKillInfo
{
	GENERATED_BODY()

public:
	
	virtual void InitializeComponent() override;

	virtual void UseActiveSkill(FName name) override;

	virtual void RangeAttackSkill(int32 attackRange) override;
	virtual AUNIT_Character* GetNearDistanceTarget(float radius) override;

	void SKill_GotMace();
	void SKill_Rush();
	void SKill_GotBless();
	void SKill_EarthQuake();


public:

	const FString SKILL_GOT_MACE = TEXT("Skill_GotMace");
	const FString SKILL_GOT_BLESS = TEXT("Skill_GotBless");
	const FString SKILL_EARTH_QUAKE = TEXT("Skill_EarthQuake");
	const FString SKILL_RUSH = TEXT("Skill_Rush");

private:

	//TMap<const FString , TFunctionRef<void>> _skillBindings;

};
