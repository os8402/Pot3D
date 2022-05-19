// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WG_GlassBallBar.generated.h"

/**
 * 
 */
UCLASS()
class POT3D_API UWG_GlassBallBar : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void SetProgressBar(float value);

};
