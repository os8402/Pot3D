// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WG_GlassBallBar.h"
#include "Stat/ACP_StatInfo.h"
#include "Misc/OutputDeviceNull.h"
#include <Components/RetainerBox.h>

void UWG_GlassBallBar::NativePreConstruct()
{
	Super::NativePreConstruct();

	auto mid = UMaterialInstanceDynamic::Create(_MI_BallMaterial, this);
	
	_RT_Box->SetEffectMaterial(mid);

}


void UWG_GlassBallBar::UpdateGauge(float value)
{
	auto mid = _RT_Box->GetEffectMaterial();
	mid->SetScalarParameterValue(TEXT("Value"), value);
	
}

