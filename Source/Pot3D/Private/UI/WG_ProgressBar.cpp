// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WG_ProgressBar.h"
#include "Components/RetainerBox.h"

//void UWG_ProgressBar::NativeOnInitialized()
void UWG_ProgressBar::NativePreConstruct()
{
	Super::NativeOnInitialized();

	UMaterialInstanceDynamic* dynamicMat = UMaterialInstanceDynamic::Create(_MI_ProgressBar, this);

	_MD_DynamicMat = dynamicMat;
	_RT_ProgressBar->SetEffectMaterial(_MD_DynamicMat);

}

void UWG_ProgressBar::SetProgressBar(float value)
{
	if(_MD_DynamicMat == nullptr)
		return;
	_MD_DynamicMat->SetScalarParameterValue("Value", value);
}
