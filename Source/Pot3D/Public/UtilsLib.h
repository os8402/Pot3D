// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#define FIND_OBJ(type, path) UtilsLib::FindObjHelper<type>(TEXT(path));
#define FIND_CLASS(type, path) UtilsLib::FindClassHelper<type>(TEXT(path));



class POT3D_API UtilsLib
{
public:
	
	template<typename t1>
	static t1* FindObjHelper(const TCHAR* path)
	{
		static ConstructorHelpers::FObjectFinder<t1> TMP(path);

		if (TMP.Succeeded())
			return TMP.Object;

		return nullptr;
	}
	template<typename t1>
	static t1* FindClassHelper(const TCHAR* path)
	{
		static ConstructorHelpers::FClassFinder<t1> TMP(path);

		if (TMP.Succeeded())
			return TMP.Class;

		return nullptr;
	}


};
