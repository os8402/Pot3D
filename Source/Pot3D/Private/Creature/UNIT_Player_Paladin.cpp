#include "Creature/UNIT_Player_Paladin.h"

#include "Skill/ACP_SKillInfo.h"
#include "Skill/ACP_SKillInfo_Paladin.h"


AUNIT_Player_Paladin::AUNIT_Player_Paladin()
{
	_chrId = 1;
	_unitJobs = EUnitJobs::PALADIN;

	_ACP_Skill = CreateDefaultSubobject<UACP_SKillInfo_Paladin>(TEXT("SKILL"));
}

void AUNIT_Player_Paladin::UseActiveSKill(FName skillName)
{
	Super::UseActiveSKill(skillName);
	_ACP_Skill->UseActiveSkill(skillName);

}