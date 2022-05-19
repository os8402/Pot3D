// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WG_NamePlateSmall.generated.h"

/**
 * 
 */
UCLASS()
class POT3D_API UWG_NamePlateSmall : public UUserWidget
{
	GENERATED_BODY()
	
public:

	void BindHp(class UACP_StatInfo* statComp);
	void UpdateHp();

private:

	TWeakObjectPtr<class UACP_StatInfo> _currentStatComp;

	UPROPERTY(meta = (BindWidget))
	class UWG_ProgressBar* WBP_ProgressBar_Percent;


	/*UPROPERTY(meta = (BindWidget))
	class UTextBlock* _TB_CharName;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* _TB_Lv;*/
};
