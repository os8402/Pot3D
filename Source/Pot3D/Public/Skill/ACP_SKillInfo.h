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

	//원형으로 타겟 서치
	bool GetOverlapSphereUnit(FVector startPos , float radius , TArray<AActor*> ignoreActors , TArray<AActor*>& outActors);

	//기본 범위형 스킬
	virtual void RangeAttackSkill(int32 attackRange);

	void PlaySkillEffect(int32 id);

	//가까운 타겟 서치
	virtual AUNIT_Character* GetNearDistanceTarget(float radius);

public:

	void SetUsingSKillId(int32 id) {_usingSkillId = id;}
	int32 GetUsingSKillId() {return _usingSkillId;}
	
	bool IsUsingSkill()
	{
		return (_usingSkillId != -1);
	}

	//나중에 스폰하면 키값을 커넥티드 아이디로 바꿔야함 
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

	/*  버프는 중복해서 걸릴 수도 있기 때문에, 비트 플래그로 검사.. 
		미정 미정 미정 미정 미정 미정 마력 체력       
		 0	 0	  0	   0    0   0    0    0   

		 ex) 체력 1, 마력 2  , 체력 + 마력 = 3
	*/
	int32 _buffFlag = 0;

private:

	UPROPERTY()
	EUnitJobs _unitJob;  

	//그 클래스가 배울 수 있는 액티브 / 패시브 모두 모음
	TMap<int32, FSkillData*> _activeSkills;
	TMap<int32, FSkillData*> _passiveSkills;

	//습득한 스킬들
	TMap<int32, FSkillData*> _acquiredSkills;


private:
	//캐릭터 대사
	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	TMap<int32 , class USoundWave*> _SOUND_CHAR_List;

	//스킬 효과음
	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	TMap<int32, class USoundWave*>  _SOUND_VFX_List;


	UPROPERTY(EditDefaultsOnly, Category = "FX")
	TMap<int32, UFXSystemAsset*> _VFX_EffList;


};
