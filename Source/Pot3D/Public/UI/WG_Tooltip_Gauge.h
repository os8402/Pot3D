// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UEnumHeader.h"
#include "WG_Tooltip_Gauge.generated.h"

class UACP_StatInfo;


UCLASS()
class POT3D_API UWG_Tooltip_Gauge : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void SetUIName(FText name) { _name = name;}
	void SetStatComp(UACP_StatInfo* statComp) { _currentStatComp = statComp;}
	void SetUIInfo(FText info) {_info = info;}
	void SetStatType(EStatTypes statType) {_statType = statType;}

	void RefreshUI();

private:

	//TWeakObjectPtr<UACP_StatInfo> _currentStatComp;
	class UACP_StatInfo* _currentStatComp;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* _TB_Name;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* _TB_Value;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* _TB_Info;

	
	FText _name; 
	FText _info;
	EStatTypes _statType;



};
