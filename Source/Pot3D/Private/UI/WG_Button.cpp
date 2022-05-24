// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WG_Button.h"

#include "Components/TextBlock.h"

void UWG_Button::NativePreConstruct()
{	
	Super::NativePreConstruct();

	_TB_Name->SetText(_btnName);
}
