// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/ACT_SeeingObject.h"

// Sets default values
AACT_SeeingObject::AACT_SeeingObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_MESH_Seeing = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH_SEEING"));
	RootComponent = _MESH_Seeing;
	_MESH_Seeing->CreateDynamicMaterialInstance(0);
	_MESH_Seeing->SetCollisionProfileName(TEXT("InvisibleWall"));

	_seeingTime = 0.3f;
	_bSeeing = false;
	_runningTimer = 0.f;

}

// Called when the game starts or when spawned
void AACT_SeeingObject::BeginPlay()
{
	Super::BeginPlay();

	PrimaryActorTick.SetTickFunctionEnable(false);
	
}

// Called every frame
void AACT_SeeingObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	_runningTimer += DeltaTime;

	float opacity = 0.f;
	if (_bSeeing)
	{
		opacity = FMath::Lerp(1.0f, 0.f, _runningTimer * (1.0f / _seeingTime));
	}
	else
	{
		opacity = FMath::Lerp(0.f, 1.0f, _runningTimer * (1.0f / _seeingTime));
	}

	_MESH_Seeing->SetScalarParameterValueOnMaterials(TEXT("Opacity"), opacity);

	if (_runningTimer > _seeingTime)
	{
		_runningTimer = 0.f;
		PrimaryActorTick.SetTickFunctionEnable(false);
	}
}

void AACT_SeeingObject::SetShowSeeingObject(bool bShow)
{
	_bSeeing = bShow;

	if (_runningTimer != 0.f)
	{
		_runningTimer = _seeingTime - _runningTimer;
	}

	PrimaryActorTick.SetTickFunctionEnable(true);
}

