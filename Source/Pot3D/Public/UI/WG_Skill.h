#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/GameDataTable.h"
#include "WG_Skill.generated.h"

class AUNIT_Player;
class UWG_Skill_List;
class UWG_IngameMain;


UCLASS()
class POT3D_API UWG_Skill : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct() override;


public:

	void InitializeUI();
	void SetSkillListData(class UScrollBox* sbList , TMap<int32, FSkillData*> skills, TArray<UWG_Skill_List*>& skillTypeList);
	void RefreshUI();

	void AcquireSkill(int32 id, FSkillData* skillData );

	UFUNCTION()
	void ConvertActiveSwitcher();
	UFUNCTION()
	void ConvertPassiveSwitcher();

public:

	void SetUIOwner(UWG_IngameMain* owner) { _UIOwner = owner; }

	void SetCurrentOwner(AUNIT_Player* player) { _currentOwner = player; }
	AUNIT_Player* GetCurrentOwner() { return _currentOwner.Get(); }

	TArray<UWG_Skill_List*> GetActiveSkillList() { return _activeSkillList;}
	TArray<UWG_Skill_List*> GetPassiveSkillList() { return _passiveSkillList;}



private:

	TWeakObjectPtr<UWG_IngameMain> _UIOwner;
	
	UPROPERTY()
	TSubclassOf<UWG_Skill_List> _skillListClass;

	TWeakObjectPtr<class AUNIT_Player> _currentOwner;

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* _WS_Switcher;

	UPROPERTY(meta = (BindWidget))
	class UWG_Button* _BTN_Active;

	UPROPERTY(meta = (BindWidget))
	class UWG_Button* _BTN_Passive;

	TArray<UWG_Skill_List*> _activeSkillList; 
	TArray<UWG_Skill_List*> _passiveSkillList; 
};
