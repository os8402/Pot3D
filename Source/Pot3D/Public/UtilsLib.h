// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <random>

#define FIND_OBJ(type, path) UtilsLib::FindObjHelper<type>(TEXT(path));
#define FIND_CLASS(type, path) UtilsLib::FindClassHelper<type>(TEXT(path));



class POT3D_API UtilsLib
{
public:
	
	
	static int NormalDistribution(float m , float s)
	{		
		std::random_device rd{};
		std::mt19937 gen{ rd() };
		std::normal_distribution<float> d(m, s);

	//	int result = abs(d(gen));

	//	if (result == 0)
	//		result++;

	//	return result;
		return d(gen);
	}

	static FText ConvertToFText(int32 data)
	{
		FString conv = FString::FromInt(data);
		FText fText = FText::FromString(conv);

		return fText;
	}
	static FText ConvertToFText(int32 data1 , int32 data2)
	{
		FString conv = FString::Printf(TEXT("%d~%d"), data1, data2);
		FText fText = FText::FromString(conv);

		return fText;
	}

	static FText ConvertToFText(FString data)
	{
		FText fText = FText::FromString(data);
		return fText;
	}

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

	template<typename t1>
	static t1* FindResoruces(const FName& name)
	{

		t1* resource = Cast<t1>(StaticLoadObject(t1::StaticClass(), NULL, *name.ToString()));

		return nullptr;
	}


};
