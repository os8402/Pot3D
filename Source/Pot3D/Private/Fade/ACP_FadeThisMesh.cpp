// Fill out your copyright notice in the Description page of Project Settings.


#include "Fade/ACP_FadeThisMesh.h"

UACP_FadeThisMesh::UACP_FadeThisMesh()
{

	PrimaryComponentTick.bCanEverTick = true;

	_fadeSpeed = 3.f;
	_transparency = 0.7f;
	_fadeToValue = 0.f;

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> M_FADE(TEXT("MaterialInstanceConstant'/Game/Resources/FadeAnything/Materials/MI_Fade5.MI_Fade5'"));
	if (M_FADE.Succeeded())
		_fadeMat = M_FADE.Object;
}


// Called when the game starts
void UACP_FadeThisMesh::BeginPlay()
{
	Super::BeginPlay();

	SetComponentTickEnabled(false);

	_SM_Static = Cast<UStaticMeshComponent>(GetOwner()->GetComponentByClass(UStaticMeshComponent::StaticClass()));

	_SM_Skeletal = Cast<USkeletalMeshComponent>(GetOwner()->GetComponentByClass(USkeletalMeshComponent::StaticClass()));

	if (_SM_Static)
		_staticMaterials = _SM_Static->GetMaterials();

	if (_SM_Skeletal)
		_skeletalMaterials = _SM_Skeletal->GetMaterials();

	for(auto mat : _staticMaterials)
		_fadeMaterials.Add(_fadeMat);

	for(auto mat : _skeletalMaterials)
		_fadeMaterials.Add(_fadeMat);

}


// Called every frame
void UACP_FadeThisMesh::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateFadeMaterialOpacity(DeltaTime);
}

void UACP_FadeThisMesh::UpdateFadeMaterialOpacity(float DeltaTime)
{
	_fadeToValue = FadeToInOrOut(DeltaTime);

	for (auto mid : _fadeArrayPerMesh)
	{
		float value = FMath::InterpEaseInOut(0.f, _transparency, _fadeToValue, 2.0);
		mid->SetScalarParameterValue("Opacity", value);
	}


	if (_fadeToValue >= 1.f)
	{
		SetComponentTickEnabled(false);
	}
	else if (_fadeToValue <= 0.f)
	{
		SetComponentTickEnabled(false);
		ResetBackToOriginMeshMaterials();
	}



}

void UACP_FadeThisMesh::FadeStart()
{
	if (_fadeMaterials.Num() == 0)
		return;

	if (_SM_Static)
		SetFadeDynamicMaterial(_SM_Static);

	else if (_SM_Skeletal)
		SetFadeDynamicMaterial(_SM_Skeletal);
}

void UACP_FadeThisMesh::FadeEnd()
{
	if (_SM_Static && _staticMaterials.Num() > 0)
	{
		TickDisabled();
	}
	else if (_SM_Skeletal && _skeletalMaterials.Num() > 0)
	{
		TickDisabled();
	}

}

float UACP_FadeThisMesh::FadeToInOrOut(float DeltaTime)
{
	float _fadeTarget = (_bIsMeshFade) ? 1.f : 0.f;

	float value = FMath::FInterpConstantTo(_fadeToValue, _fadeTarget, DeltaTime, _fadeSpeed);

	return value;
}


void UACP_FadeThisMesh::ReplaceMeshMaterialsByFadeMaterials(UPrimitiveComponent* curMesh)
{
	if (curMesh == nullptr)
		return;

	for (int i = 0; i < _fadeArrayPerMesh.Num(); i++)
	{
		curMesh->SetMaterial(i, _fadeArrayPerMesh[i]);

	}

	_bIsMeshFade = true;
	SetComponentTickEnabled(true);
}

void UACP_FadeThisMesh::ResetBackToOriginMeshMaterials()
{
	if (_SM_Static && _staticMaterials.Num() > 0)
	{
		for (int i = 0; i < _staticMaterials.Num(); i++)
			_SM_Static->SetMaterial(i, _staticMaterials[i]);
	}
	else if (_SM_Skeletal && _skeletalMaterials.Num() > 0)
	{
		for (int i = 0; i < _skeletalMaterials.Num(); i++)
			_SM_Skeletal->SetMaterial(i, _skeletalMaterials[i]);
	}
}

void UACP_FadeThisMesh::SetFadeDynamicMaterial(UPrimitiveComponent* curMesh)
{
	if (_fadeArrayPerMesh.Num() == 0)
	{
		for (auto mat : _fadeMaterials)
		{
			auto mid = UMaterialInstanceDynamic::Create(mat, this);

			_fadeArrayPerMesh.Add(mid);
		}
	}

	ReplaceMeshMaterialsByFadeMaterials(curMesh);
}

void UACP_FadeThisMesh::TickDisabled()
{
	if (_fadeArrayPerMesh.Num() > 0)
	{
		_bIsMeshFade = false;
		SetComponentTickEnabled(true);
	}
}
