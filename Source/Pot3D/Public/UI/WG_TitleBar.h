// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WG_TitleBar.generated.h"

/**
 * 
 */
UCLASS()
class POT3D_API UWG_TitleBar : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetTitle(FText name);

private:

	UPROPERTY(meta = (BindWidget))
	class UImage* _IMG_Grade;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* _TB_Name;

	
};
