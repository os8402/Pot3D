// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WG_DamgeText.generated.h"

/**
 * 
 */
UCLASS()
class POT3D_API UWG_DamgeText : public UUserWidget
{
	GENERATED_BODY()

public:
	void UpdateText(int32 dmg, FLinearColor color);

private:

	UPROPERTY(meta=(BindWidget))
	class UTextBlock* _TB_DmgText;
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* _WA_Fade;

	

	
};
