// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WG_BonusStat.generated.h"

/**
 * 
 */
UCLASS()
class POT3D_API UWG_BonusStat : public UUserWidget
{
	GENERATED_BODY()

public:
	
	void SetBonusStatText(FText text , FLinearColor color);

private:

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* _TB_BonusStat;
};

