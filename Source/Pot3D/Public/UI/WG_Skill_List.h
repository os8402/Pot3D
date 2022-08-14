// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/GameDataTable.h"
#include "UEnumHeader.h"
#include "WG_Skill_List.generated.h"

class UWG_Skill;
class UWG_Skill_Slot;


UCLASS()
class POT3D_API UWG_Skill_List : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct() override;

	void SetSkillData(FSkillData* skillData , bool bAcquired);

	UFUNCTION()
	void AcquireSkill();
	UFUNCTION()
	void RemoveSkill();

	void SetUIOwner(UWG_Skill* skill) {	if (skill) 	_UIOwner = skill; }

	void SaveSkillData(ESaveType type);
	
	UWG_Skill_Slot* GetSkillSlot() {return _WBP_Skill_Slot;}

private:
	
	
	TWeakObjectPtr<UWG_Skill> _UIOwner;
	FSkillData*_skillData; 

	UPROPERTY(meta = (BindWidget))
	UWG_Skill_Slot* _WBP_Skill_Slot;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* _TB_SkillName;


	UPROPERTY(meta = (BindWidget))
	class URichTextBlock* _RTB_ReduceMana;
	UPROPERTY(meta = (BindWidget))
	class URichTextBlock* _RTB_CoolTime;
	UPROPERTY(meta = (BindWidget))
	class URichTextBlock* _RTB_SkillInfo;
	UPROPERTY(meta = (BindWidget))
	class UButton* _BTN_AddSkill;
	UPROPERTY(meta = (BindWidget))
	class UButton* _BTN_RemoveSkill;
	UPROPERTY(meta = (BindWidget))
	class UBorder* _BD_Lock;

};
