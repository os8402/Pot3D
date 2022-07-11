// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WG_ProgressBar.generated.h"

/**
 * 
 */
UCLASS()
class POT3D_API UWG_ProgressBar : public UUserWidget
{
	GENERATED_BODY()




protected:
	virtual void NativePreConstruct();

public:
	UFUNCTION()
	void SetProgressBar(float value);

private:

	UPROPERTY(meta = (BindWidget))
	class URetainerBox* _RT_ProgressBar;

	UPROPERTY(EditAnywhere,BlueprintReadWrite , meta = (AllowPrivateAccess = true))
	class UMaterialInterface* _MI_ProgressBar;

	UPROPERTY(VisibleAnyWhere)
	class UMaterialInstanceDynamic* _MD_DynamicMat;

};
