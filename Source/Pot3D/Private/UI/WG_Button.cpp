// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WG_Button.h"

#include "Components/TextBlock.h"
#include "Components/Image.h"

void UWG_Button::NativePreConstruct()
{	
	Super::NativePreConstruct();

	if (_texture != nullptr)
	{	
		_IMG_Icon->SetBrushFromTexture(_texture);
		_IMG_Icon->SetColorAndOpacity(_iconColor);
	}


	_TB_Name->SetText(_btnName);
}

