#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/GameDataTable.h"
#include "Manager/GI_GmInst.h" 
#include "UtilsLib.h"
#include "ACP_SKillInfo.generated.h"

class AUNIT_Character;
class UNiagaraComponent;
class UNiagaraSystem;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class POT3D_API UACP_SKillInfo : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UACP_SKillInfo();

protected:

	virtual void InitializeComponent() override;

public:

	virtual void SetSkillData(EUnitJobs job);
	void SetAcquireSkill(int32 id , FSkillData* skillData);

	virtual void UseActiveSkill(FName name);

	//�������� Ÿ�� ��ġ
	bool GetOverlapSphereUnit(FVector startPos , float radius , TArray<AActor*> ignoreActors , TArray<AActor*>& outActors);

	//�⺻ ������ ��ų
	virtual void RangeAttackSkill(int32 attackRange);

	void PlaySkillEffect(int32 id);

	//����� Ÿ�� ��ġ
	virtual AUNIT_Character* GetNearDistanceTarget(float radius);

public:

	void SetUsingSKillId(int32 id) {_usingSkillId = id;}
	int32 GetUsingSKillId() {return _usingSkillId;}
	
	bool IsUsingSkill()
	{
		return (_usingSkillId != -1);
	}

	//���߿� �����ϸ� Ű���� Ŀ��Ƽ�� ���̵�� �ٲ���� 
	TArray<AUNIT_Character*>   GetSkillTargetEnemy() {return _skillTargetEnemys;};


	EUnitJobs GetUnitJobs() {return _unitJob;}
	TMap<int32 , FSkillData*> GetActiveSkills() {return _activeSkills;}
	TMap<int32 , FSkillData*> GetPassiveSkills() {return _passiveSkills;}
	TMap<int32 , FSkillData*> GetAcquiredSkills() {return _acquiredSkills;}

	FSkillData* GetAcquireSKill(int32 id) { return _acquiredSkills[id]; }

	void RegisterPassiveSkill(int32 id, FSkillData* skillData);

	//TMap<int32, class USoundWave*> GetSoundCharSoundList() {return _SOUND_CHAR_List;}
	//TMap<int32, class USoundWave*> GetSoundVFXSoundList() {return _SOUND_VFX_List;}

	class USoundWave* GetSoundCharSound(int32 id) {return (_SOUND_CHAR_List.Num() > 0) ? _SOUND_CHAR_List[id] : nullptr ; }
	class USoundWave* GetSoundVFXSound(int32 id) {return (_SOUND_VFX_List.Num() > 0) ? _SOUND_VFX_List[id] : nullptr;}
	class UFXSystemAsset* GetVFXEffect(int32 id) {return (_VFX_EffList.Num() > 0) ? _VFX_EffList[id] : nullptr;}
	
	bool IsAcquiredSkill(int32 id) 
	{
		if(_acquiredSkills.Num() == 0)
			return false;

		if(_acquiredSkills.Find(id) == false)
			return false;
		
		return true;
	};

	FName GetSkillNameFromId(int32 id)
	{
		return _acquiredSkills[id]->_skillName;
	}

protected:
	
	TArray<FName> _unitSkillNames;

protected:

	//
	//Skill 
	// 
	int32 _usingSkillId = -1;
	TArray<AUNIT_Character*>  _skillTargetEnemys;

	/*  ������ �ߺ��ؼ� �ɸ� ���� �ֱ� ������, ��Ʈ �÷��׷� �˻�.. 
		���� ���� ���� ���� ���� ���� ���� ü��       
		 0	 0	  0	   0    0   0    0    0   

		 ex) ü�� 1, ���� 2  , ü�� + ���� = 3
	*/
	int32 _buffFlag = 0;

private:

	UPROPERTY()
	EUnitJobs _unitJob;  

	//�� Ŭ������ ��� �� �ִ� ��Ƽ�� / �нú� ��� ����
	TMap<int32, FSkillData*> _activeSkills;
	TMap<int32, FSkillData*> _passiveSkills;

	//������ ��ų��
	TMap<int32, FSkillData*> _acquiredSkills;


private:
	//ĳ���� ���
	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	TMap<int32 , class USoundWave*> _SOUND_CHAR_List;

	//��ų ȿ����
	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	TMap<int32, class USoundWave*>  _SOUND_VFX_List;


	UPROPERTY(EditDefaultsOnly, Category = "FX")
	TMap<int32, UFXSystemAsset*> _VFX_EffList;


};
