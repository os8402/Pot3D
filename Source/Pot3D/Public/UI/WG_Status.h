// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UtilsLib.h"
#include "WG_Status.generated.h"

/**
 * 
 */
UCLASS()
class POT3D_API UWG_Status : public UUserWidget
{
	GENERATED_BODY()


public:
	void RefreshStat(class UACP_StatInfo* statComp);



private:

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* _TB_Stat_Lv;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* _TB_Stat_Str;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* _TB_Stat_Dex;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* _TB_Stat_Int;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* _TB_Stat_Luk;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* _TB_Stat_Atk;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* _TB_Stat_Def;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* _TB_Stat_Res;
	
};
