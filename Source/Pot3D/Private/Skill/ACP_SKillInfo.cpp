#include "Skill/ACP_SKillInfo.h"
#include <Kismet/GameplayStatics.h>

#include <Particles/ParticleSystemComponent.h>

#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"

#include "Creature/UNIT_Character.h"
#include "Stat/ACP_StatInfo.h"

#include "UI/WG_Buff.h"
#include "UI/WG_IngameMain.h"
#include "UI/WG_MainBar.h"

#include "Controller/UNIT_PlayerCT.h"


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

	//SOUND , VFX

	for (const auto& skill : _activeSkills)
	{
		FName unitSoundPath = skill.Value->_unitSoundPath;
		FName vfxSoundPath = skill.Value->_vfxSoundPath;
		//�̵��� ����
		FName vfxEffPath = skill.Value->_vfxEffectPath;

	
		USoundWave* unitSoundWav =  Cast<USoundWave>(
			StaticLoadObject(USoundWave::StaticClass(), nullptr, *unitSoundPath.ToString()));

		if(unitSoundWav)
			_SOUND_CHAR_List.Add(skill.Key, unitSoundWav);

		USoundWave* vfxSoundWav = Cast<USoundWave>(
			StaticLoadObject(USoundWave::StaticClass(), nullptr, *vfxSoundPath.ToString()));

		if(vfxSoundWav)
			_SOUND_VFX_List.Add(skill.Key,  vfxSoundWav);
	
		//���� ���Ž� ����Ʈ
		UParticleSystem* vfxEff = nullptr;
		UtilsLib::GetAssetDynamic(&vfxEff, *vfxEffPath.ToString());
		//���̾ư��� ��
		UNiagaraSystem* vfxNiagaraEff = nullptr;
		UtilsLib::GetAssetDynamic(&vfxNiagaraEff, *vfxEffPath.ToString());
	
		if(vfxEff)
			_VFX_EffList.Add(skill.Key, vfxEff);
				
		if (vfxNiagaraEff)
			_VFX_EffList.Add(skill.Key, vfxNiagaraEff);

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

	ESkillTypes skillType = skillData->_skillType;

	//�нú��� ��� �������� ����
	if (skillType == ESkillTypes::PASSIVE)
	{
		RegisterPassiveSkill(id, skillData);

	}

}

void UACP_SKillInfo::RegisterPassiveSkill(int32 id, FSkillData* skillData)
{
	int32 len = skillData->_values.Num();
	
	FStatData statData;
	TMap<int32, int32> bonusStats;

	AUNIT_Character* owner = Cast<AUNIT_Character>(GetOwner());

	AUNIT_PlayerCT* pc = Cast<AUNIT_PlayerCT>(owner->GetController());

	for (int32 i = 0; i < len; i++)
	{
		int32 value = skillData->_values[i];
		EBuffTypes buffType = skillData->_buffTypes[i];

		switch (buffType)
		{

		case EBuffTypes::HP:
			statData._maxHp += value;
			break;
		case EBuffTypes::MP:
			statData._maxMp += value;
			break;
		case EBuffTypes::RESILIENCE:
			statData._resilience += value;
			break;
		case EBuffTypes::ATTACK_SPEED:
			break;
		case EBuffTypes::MOVE_SPEED:
			break;
		case EBuffTypes::STRENGH:
			statData._strength += value;
			break;
		case EBuffTypes::DEXTERITY:
			statData._dexterity += value;
			break;
		case EBuffTypes::INTELIGENCE:
			statData._intelligence += value;
			break;
		case EBuffTypes::LUCK:
			statData._luck += value;
			break;
		default:
			break;
		}

		//TODO : ��������Ʈ�� ���
		if (pc)
			pc->GetMainUI()->GetMainBar()->AddBuffList(value , buffType);

	}


	 owner->GetStatComp()->RefreshStat(statData , bonusStats);

}


void UACP_SKillInfo::UseActiveSkill(FName name)
{
	_skillTargetEnemys.Empty();
}

bool UACP_SKillInfo::GetOverlapSphereUnit(FVector startPos, float radius, TArray<AActor*> ignoreActors , TArray<AActor*>& outActors)
{

	TArray<TEnumAsByte<EObjectTypeQuery>> objectTypes;

	objectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));

	bool result = UKismetSystemLibrary::SphereOverlapActors
	(
		GetWorld(),
		startPos,
		radius,
		objectTypes,
		nullptr,
		ignoreActors,
		outActors
	);

	return result;

}

void UACP_SKillInfo::RangeAttackSkill(int32 attackRange)
{
	
}

void UACP_SKillInfo::PlaySkillEffect(int32 id)
{

//���Žó� ���̾ư��� �� �� �ش��ϴ� �� ����.. 
	if (_VFX_EffList.Find(id) == false)
		return;
	
	FTransform spawnTransform = GetOwner()->GetActorTransform();


	auto character = Cast<AUNIT_Character>(GetOwner());
	
	if (character)
	{
		spawnTransform.SetLocation(FVector::ZeroVector);
		spawnTransform.SetRotation(FQuat::Identity);

		UtilsLib::PlayEffect(GetWorld(), _VFX_EffList[id], spawnTransform, character->GetMesh());
	}
		
	else
		UtilsLib::PlayEffect(GetWorld(), _VFX_EffList[id], spawnTransform);



}

AUNIT_Character* UACP_SKillInfo::GetNearDistanceTarget(float radius)
{
	return nullptr;
}

