// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WG_Skill_List.generated.h"

/**
 * 
 */
UCLASS()
class POT3D_API UWG_Skill_List : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct() override;

private:

	UPROPERTY(meta = (BindWidget))
	class UWG_Skill_Slot* _WBP_SkillSlot;

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
