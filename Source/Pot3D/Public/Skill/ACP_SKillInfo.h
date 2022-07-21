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

	//그 클래스가 배울 수 있는 액티브 / 패시브 모두 모음
	TMap<int32, FSkillData*> _activeSkills;
	TMap<int32, FSkillData*> _passiveSkills;

	//습득한 스킬들
	TMap<int32, FSkillData*> _acquiredSkills;


};
