// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <random>

#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

#include <Components/AudioComponent.h>

#include "Particles/ParticleSystem.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"

//#define FIND_OBJ(type, path) UtilsLib::FindObjHelper<type>(TEXT(path));
//#define FIND_CLASS(type, path) UtilsLib::FindClassHelper<type>(TEXT(path));



class POT3D_API UtilsLib
{
public:
	
	template<typename T>
	static void GetAsset(T** outObject, FString path)
	{
		ConstructorHelpers::FObjectFinder<T> asset(*path);
		
		if (asset.Succeeded())
			*outObject =  asset.Object;
		
	}

	template<typename T>
	static void GetAssetDynamic(T** outObject, FString path)
	{
		*outObject = Cast<T>(StaticLoadObject(T::StaticClass() , nullptr , *path));
	}

	template<typename T>
	static void GetClass(TSubclassOf<T>* outClass, FString path)
	{
		ConstructorHelpers::FClassFinder<T> asset(*path);
		*outClass = asset.Class;

	}

	template<typename T>
	static void GetTSubClass(TSubclassOf<T>* outClass, FString path)
	{
		UClass* loadClass = StaticLoadClass(T::StaticClass(), nullptr, *path);
		*outClass = loadClass;

	}

	template<typename T>
	static void CreateComponent(AActor* actor, T** outComponent, FName name, USceneComponent* parent = nullptr)
	{
		*outComponent = actor->CreateDefaultSubobject<T>(name);

		if (!!parent)
		{
			(*outComponent)->SetupAttachment(parent);

			return;
		}

		actor->SetRootComponent(*outComponent);

	}
	template<typename T>
	static void CreateActorComponent(AActor* actor, T** outComponent, FName name)
	{
		*outComponent = actor->CreateDefaultSubobject<T>(name);
	}

	template<typename T>
	static T* FindActor(UWorld* world, int32 index = 0)
	{
		TArray<AActor*> actors;
		UGameplayStatics::GetAllActorsOfClass(world, T::StaticClass() , actors);

		if(actors.Num() < 1)
			return nullptr;

		return Cast<T>(actors[index]);

	}

	template<typename T>
	static void FindActors(UWorld* InWorld, TArray<T*>& OutActors)
	{
		TArray<AActor*> actors;
		UGameplayStatics::GetAllActorsOfClass(InWorld, T::StaticClass(), actors);

		for (AActor* actor : actors)
		{
			T* obj = Cast<T>(actor);

			if (!!obj)
				OutActors.Add(obj);
		}
	}


	template<typename T>
	static T* FindAsset(const FName& name)
	{

		T* resource = Cast<T>(StaticLoadObject(T::StaticClass(), NULL, *name.ToString()));

		return nullptr;
	}

	template<typename T>
	static T* GetComponent(AActor* actor)
	{
		return Cast<T>(actor->GetComponentByClass(T::StaticClass));

	}

	template<typename T>
	static T* GetComponent(AActor* actor, FString name)
	{
		TArray<T*> components;
		actor->GetComponents<T>(components);

		for (T* component : components)
		{
			if(component->GetName() == name)
				return component;
		}

		return nullptr;
	}

	static FString GetStringFromEnum(FString InTypeName, int32 InIndex)
	{
		UEnum* ptr = FindObject<UEnum>(ANY_PACKAGE, *InTypeName, true);
		return ptr->GetNameStringByIndex(InIndex);
	}

	static FLinearColor GetRandomColor()
	{
		FLinearColor color;
		color.R = UKismetMathLibrary::RandomFloatInRange(0, 1);
		color.G = UKismetMathLibrary::RandomFloatInRange(0, 1);
		color.B = UKismetMathLibrary::RandomFloatInRange(0, 1);
		color.A = 1.0f;

		return color;
	}

	
	
	static int NormalDistribution(float m , float s)
	{		
		std::random_device rd{};
		std::mt19937 gen{ rd() };
		std::normal_distribution<float> d(m, s);

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
	static FText IsBonusStat(int32 stat , int32* bonusStat)
	{
		FString str;
		
		if (*bonusStat > 0)
			str = FString::Printf(TEXT("%d<Green>(+%d)</>"), stat, *bonusStat);
		else
			str = FString::FromInt(stat);
		

		FText fText = FText::FromString(str);
		return fText;
	}
	static FText IsBonusStat(int32 stat, int32 bonusStat)
	{
		FString str;

		if (bonusStat > 0)
			str = FString::Printf(TEXT("%d<Green>(+%d)</>"), stat, bonusStat);
		else
			str = FString::FromInt(stat);


		FText fText = FText::FromString(str);
		return fText;
	}
	static FText IsBonusStat(int32 minAtk, int32 maxAtk, int32 bonusMinAtk, int32 bonusMaxAtk)
	{
		FString str;

		if (bonusMinAtk > 0 || bonusMaxAtk > 0)
			str = FString::Printf(TEXT("%d~%d<Green>(+%d~%d)</>"), minAtk ,maxAtk ,bonusMinAtk, bonusMaxAtk);
		else
			return ConvertToFText(minAtk, maxAtk);


		FText fText = FText::FromString(str);
		return fText;
	
	
	}

	static void PlayEffect(UWorld* InWorld, UFXSystemAsset* InEffect, FTransform& InTransform, USkeletalMeshComponent* InMesh = NULL, FName InSocketName = NAME_None)
	{
		UParticleSystem* particle = Cast<UParticleSystem>(InEffect);
		UNiagaraSystem* niagara = Cast<UNiagaraSystem>(InEffect);

		FVector location = InTransform.GetLocation();
		FRotator rotation = FRotator(InTransform.GetRotation());
		FVector scale = InTransform.GetScale3D();
		if (InMesh)
		{
			if (particle)
			{
				UGameplayStatics::SpawnEmitterAttached(particle, InMesh, InSocketName, location, rotation, scale);

				return;
			}

			if (niagara)
			{
				UNiagaraFunctionLibrary::SpawnSystemAttached(niagara, InMesh, InSocketName, location, rotation, scale, EAttachLocation::KeepRelativeOffset, true, ENCPoolMethod::None);

				return;
			}
		}

		if (particle)
		{
			UGameplayStatics::SpawnEmitterAtLocation(InWorld, particle, InTransform);

			return;
		}

		if (niagara)
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(InWorld, niagara, location, rotation, scale);
	}

	template<typename T>
	static T* MakeSpawnActor(UWorld* InWorld , TSubclassOf<AActor> InActor, AActor* InParent)
	{
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = InParent;

		FVector spawnPos = InParent->GetActorLocation();
		FRotator spawnRot = InParent->GetActorRotation();
	
		T* spawnActor = Cast<T>(
			InWorld->SpawnActor<AActor>(InActor, spawnPos, spawnRot, spawnParams));
		
		return spawnActor;
	}


	static void SoundPlay(UWorld* world , USoundWave* wav , FVector pos)
	{
		if(world  == nullptr || wav == nullptr)
			return;

		UGameplayStatics::PlaySoundAtLocation(world, wav, pos);
	}
	

	static void SoundPlay2D(UWorld* world, USoundWave* wav)
	{
		UGameplayStatics::PlaySound2D(world, wav);
	}
};
