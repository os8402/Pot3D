#pragma once

#include "CoreMinimal.h"
#include "Skill/ACP_SKillInfo.h"
#include "ACP_SKillInfo_Paladin.generated.h"

UCLASS()
class POT3D_API UACP_SKillInfo_Paladin : public UACP_SKillInfo
{
	GENERATED_BODY()

public:
	
	virtual void InitializeComponent() override;

	virtual void UseActiveSkill(FName name) override;

	void SKill_GotMace();
	void SKill_BoneCrush();
	void SKill_GotBless();
	void SKill_EarthCrush();


public:

	const FString SKILL_GOT_MACE = TEXT("Skill_GotMace");
	const FString SKILL_GOT_BLESS = TEXT("Skill_GotBless");
	const FString SKILL_GOT_EARTH_CRUSH = TEXT("Skill_EarthCrush");
	const FString SKILL_GOT_BONE_CRUSH = TEXT("Skill_BoneCrush");

private:

	//TMap<const FString , TFunctionRef<void>> _skillBindings;

};
