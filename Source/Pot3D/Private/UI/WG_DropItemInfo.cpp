// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WG_DropItemInfo.h"
#include "Components/TextBlock.h"

void UWG_DropItemInfo::BindItemInfo(FText name , int32 count)
{
	FString conv = FString::Printf(TEXT("%s %d"), *name.ToString(), count);

	_TB_ItemName->SetText(FText::FromString(conv));

}
