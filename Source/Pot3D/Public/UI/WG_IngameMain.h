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

	void BindHp(class UACP_StatInfo* statComp);
	void UpdateHp();

public:
	class UCanvasPanel* GetMonsterInfoPanel() { return _CP_MonsterInfo; }

public :

	UPROPERTY(meta = (BindWidget))
	class UImage* IMG_Main;


	UPROPERTY(meta = (BindWidget))
	class UProgressBar* _PB_HpMainBar;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* _PB_MpMainBar;

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* _CP_MonsterInfo;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* _PB_MonsterInfoHpBar;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* _TB_MonsterInfoName;

	TWeakObjectPtr<class UACP_StatInfo> _currentStatComp;
	
};
