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

public:
	EUnitJobs GetUnitJobs() {return _unitJob;}
	TMap<int32 , FSkillData*> GetActiveSkills() {return _activeSkills;}
	TMap<int32 , FSkillData*> GetPassiveSkills() {return _passiveSkills;}

private:

	UPROPERTY()
	EUnitJobs _unitJob;  

	TMap<int32, FSkillData*> _activeSkills;
	TMap<int32, FSkillData*> _passiveSkills;


};
