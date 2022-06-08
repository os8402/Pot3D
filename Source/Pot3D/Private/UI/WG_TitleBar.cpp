// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WG_TitleBar.h"

#include <Components/Image.h>
#include <COmponents/TextBlock.h>

void UWG_TitleBar::SetTitle(FText name)
{
	//TODO : 등급 + 텍스트 설정
	
	_TB_Name->SetText(name);

	//
}

void UWG_TitleBar::SetGradeTexture(UTexture2D* texure)
{
	_IMG_Grade->SetBrushFromTexture(texure);
}
