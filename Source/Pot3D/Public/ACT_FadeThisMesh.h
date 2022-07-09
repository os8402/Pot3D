// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ACT_FadeThisMesh.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class POT3D_API UACT_FadeThisMesh : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UACT_FadeThisMesh();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	void UpdateFadeMaterialOpacity();
	void FadeStart();
	void FadeEnd();
	void FadeToInOrOut();
	void ReplaceMeshMaterialsByFadeMaterials();
	void ResetBackToOriginMeshMaterials();

private:

	UPROPERTY(EditAnywhere, Category = "Fade Option", meta = (AllowPrivateAccess = true))
	TArray<UMaterialInterface*> _fadeMaterials;

	UPROPERTY(EditAnywhere, Category ="Fade Option" , meta = (AllowPrivateAccess = true))
	float _fadeSpeed;
	UPROPERTY(EditAnywhere, Category = "Fade Option", meta = (AllowPrivateAccess = true))
	float _transparency;

};
