// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WG_IngameMain.generated.h"

/**
 * 
 */
UCLASS()
class POT3D_API UWG_IngameMain : public UUserWidget
{
	GENERATED_BODY()

public:

	void BindStat(class UACP_StatInfo* statComp);
	void BindCreatureInfo();

	void UpdateHp();
	void OpenInventory();

public:
	class UWG_NamePlate* GetNamePlate() { return _WBP_NamePlate_1; }

public :

	UPROPERTY(meta = (BindWidget))
	class UImage* IMG_Main;


	/*UPROPERTY(meta = (BindWidget))
	class UProgressBar* _PB_HpMainBar;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* _PB_MpMainBar;*/

	UPROPERTY(meta = (BindWidget))
	class UWG_NamePlate* _WBP_NamePlate_1;

	//UPROPERTY(meta = (BindWidget))
	//class UProgressBar* _PB_MonsterInfoHpBar;

	//UPROPERTY(meta = (BindWidget))
	//class UTextBlock* _TB_MonsterInfoName;

	TWeakObjectPtr<class UACP_StatInfo> _currentStatComp;

//	UPROPERTY(meta = (BindWidget))
//	class UWG_GlassBallBar* _GB_HpBar;

	UPROPERTY(meta = (BindWidget))
	class UWG_Inventory* _WBP_Inventory;
	
};
