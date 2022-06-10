// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class POT3D_API LocalizationUI
{

public:
	static FString ConvertToUIText(FString str)
	{
		FString conv;

		if(str == "STRENGH")
			conv = FString(TEXT("힘"));
		else if (str == "DEXTERITY")
			conv = FString(TEXT("민첩"));
		else if (str == "INTELIGENCE")
			conv = FString(TEXT("마력"));
		else if (str == "RESILIENCE")
			conv = FString(TEXT("회복력"));
		else if (str == "LUCK")
			conv = FString(TEXT("운"));

		else if(str == "HP")
			conv = FString(TEXT("체력"));
		else if (str == "MP")
			conv = FString(TEXT("마력"));
	

		return conv;

	}

};
