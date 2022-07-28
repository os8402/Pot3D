#include "Skill/ACP_SKillInfo.h"
#include <Kismet/GameplayStatics.h>

#include "Creature/UNIT_Character.h"

UACP_SKillInfo::UACP_SKillInfo()
{

	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;

}

void UACP_SKillInfo::InitializeComponent()
{
	Super::InitializeComponent();
}

//�ϴ� �нú�.. ������ �� �ҷ��;� �ϸ�.
//Ŭ������ �´� ��Ƽ�� ��ų�� �� �����;� �մϴ�.

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
				_activeSkills.Add(id, skillDatas[i]);

			}
			else if (skillType == ESkillTypes::PASSIVE)
			{
				_passiveSkills.Add(id, skillDatas[i]);
			}

		}

	}
}


void UACP_SKillInfo::SetAcquireSkill(int32 id, FSkillData* skillData)
{
	if (_acquiredSkills.Find(id))
		return;

	FString skillStr = FString::Printf(TEXT("Acquire Skill Id : %d"), id);
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, skillStr);

	//��� 
	_acquiredSkills.Add(id , skillData);

}

void UACP_SKillInfo::UseActiveSkill(FName name)
{
	
}

