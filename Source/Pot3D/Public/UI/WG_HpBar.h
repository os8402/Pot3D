// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WG_HpBar.generated.h"

/**
 * 
 */
UCLASS()
class POT3D_API UWG_HpBar : public UUserWidget
{
	GENERATED_BODY()


public:

	void BindHp(class UACP_StatInfo* statComp, FText name);
	void UpdateHp();

private:

	TWeakObjectPtr<class UACP_StatInfo> _currentStatComp;

	UPROPERTY(meta=(BindWidget))
	class UProgressBar* _PB_Hpbar;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* _TB_NameLv;


	
};
