// Fill out your copyright notice in the Description page of Project Settings.


#include "ACT_FadeThisMesh.h"

// Sets default values for this component's properties
UACT_FadeThisMesh::UACT_FadeThisMesh()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	_fadeSpeed = 5.f;
	_transparency = 0.8f;


	// ...
}


// Called when the game starts
void UACT_FadeThisMesh::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UACT_FadeThisMesh::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UACT_FadeThisMesh::UpdateFadeMaterialOpacity()
{
		
}

void UACT_FadeThisMesh::FadeStart()
{

}

void UACT_FadeThisMesh::FadeEnd()
{

}

void UACT_FadeThisMesh::FadeToInOrOut()
{

}

void UACT_FadeThisMesh::ReplaceMeshMaterialsByFadeMaterials()
{

}

void UACT_FadeThisMesh::ResetBackToOriginMeshMaterials()
{

}

