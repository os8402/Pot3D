#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/GameDataTable.h"
#include "Manager/GI_GmInst.h" 
#include "ACP_SKillInfo.generated.h"


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

	void SetSkillData(EUnitJobs job);
	void SetAcquireSkill(int32 id , FSkillData* skillData);

public:
	EUnitJobs GetUnitJobs() {return _unitJob;}
	TMap<int32 , FSkillData*> GetActiveSkills() {return _activeSkills;}
	TMap<int32 , FSkillData*> GetPassiveSkills() {return _passiveSkills;}
	TMap<int32 , FSkillData*> GetAcquiredSkills() {return _acquiredSkills;}

	bool IsAcquiredSkill(int32 id) 
	{
		if(_acquiredSkills.Num() == 0)
			return false;

		if(_acquiredSkills.Find(id) == false)
			return false;
		
		return true;
	};

private:

	UPROPERTY()
	EUnitJobs _unitJob;  

	//�� Ŭ������ ��� �� �ִ� ��Ƽ�� / �нú� ��� ����
	TMap<int32, FSkillData*> _activeSkills;
	TMap<int32, FSkillData*> _passiveSkills;

	//������ ��ų��
	TMap<int32, FSkillData*> _acquiredSkills;


};
