// Fill out your copyright notice in the Description page of Project Settings.


#include "ACT_SeeThrough.h"

// Sets default values
AACT_SeeThrough::AACT_SeeThrough()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_MESH_SeeThrough = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH_SEEING_THROUGH"));
	RootComponent = _MESH_SeeThrough;
	_MESH_SeeThrough->CreateDynamicMaterialInstance(0);
	_MESH_SeeThrough->SetCollisionProfileName(TEXT("InvisibleWall"));

	_seeThroughTime = 0.3f;
	_runningTime = 0.f;
	_bSeeing = false;

}

// Called when the game starts or when spawned
void AACT_SeeThrough::BeginPlay()
{
	Super::BeginPlay();

	PrimaryActorTick.SetTickFunctionEnable(false);

	
}

// Called every frame
void AACT_SeeThrough::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	_runningTime += DeltaTime;

	float opacity = 0.f;
	if (_bSeeing)
	{
		opacity = FMath::Lerp(1.f, 0.2f, _runningTime * (1.f / _seeThroughTime));
	}
	else
	{
		opacity = FMath::Lerp(0.2f, 1.f, _runningTime * (1.f / _seeThroughTime));
	}

	_MESH_SeeThrough->SetScalarParameterValueOnMaterials(TEXT("Opacity") , opacity);

	if (_runningTime > _seeThroughTime)
	{
		_runningTime = 0.f;
		PrimaryActorTick.SetTickFunctionEnable(false);
	}

}

void AACT_SeeThrough::SetShowThisActor(bool bShow)
{
	
	_bSeeing = bShow;

	if (_runningTime != 0.f)
	{
		_runningTime = _seeThroughTime - _runningTime;

	}

	PrimaryActorTick.SetTickFunctionEnable(true);
}

