// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WG_MainBar.generated.h"

/**
 * 
 */
UCLASS()
class POT3D_API UWG_MainBar : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativePreConstruct() override;
	void BindStat(class UACP_StatInfo* statComp);
	void UpdateHp();

	void SetGaugeTooltipHovered();

private:
	
	TWeakObjectPtr<class UACP_StatInfo> _currentStatComp;

	UPROPERTY(meta = (BindWidget))
	class UWG_GlassBallBar* _GB_HpBar;
	UPROPERTY(meta = (BindWidget))
	class UWG_GlassBallBar* _GB_MpBar;

	UPROPERTY(meta = (BindWidget))
	class UWG_Tooltip_Gauge* _WBP_Tooltip_Hp;
	UPROPERTY(meta = (BindWidget))
	class UWG_Tooltip_Gauge* _WBP_Tooltip_Mp;





};
