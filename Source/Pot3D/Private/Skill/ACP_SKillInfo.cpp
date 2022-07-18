#include "Skill/ACP_SKillInfo.h"
#include <Kismet/GameplayStatics.h>

UACP_SKillInfo::UACP_SKillInfo()
{

	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;

}

void UACP_SKillInfo::InitializeComponent()
{
	Super::InitializeComponent();
}

//일단 패시브.. 무조건 다 불러와야 하며.
//클래스에 맞는 액티브 스킬도 다 가져와야 합니다.

void UACP_SKillInfo::SetSkillData(EUnitJobs job)
{
	_unitJob = job;

	auto gmInst = Cast<UGI_GmInst>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (gmInst)
	{
		TArray<FSkillData*> skillDatas = gmInst->GetSkillDatas();

		for (int32 i = 0; i < skillDatas.Num(); i++)
		{
			int32 id = skillDatas[i]->_skillId;
			ESkillTypes skillType = skillDatas[i]->_skillType;

			if (_unitJob == skillDatas[i]->_job && skillType == ESkillTypes::ACTIVE)
			{
				_activeSkills.Add(id , skillDatas[i]);
				
			}
			else if (skillType == ESkillTypes::PASSIVE)
			{
				_passiveSkills.Add(id , skillDatas[i]);
			}

		}

	}
}

