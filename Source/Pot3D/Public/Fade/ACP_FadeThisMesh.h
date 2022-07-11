// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ACP_FadeThisMesh.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class POT3D_API UACP_FadeThisMesh : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UACP_FadeThisMesh();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
public:
	void UpdateFadeMaterialOpacity(float DeltaTime);
	void FadeStart();
	void FadeEnd();
	float FadeToInOrOut(float DeltaTime);
	void ReplaceMeshMaterialsByFadeMaterials(UPrimitiveComponent* curMesh);
	void ResetBackToOriginMeshMaterials();

	void SetFadeDynamicMaterial(UPrimitiveComponent* curMesh );
	void TickDisabled();

private:

	UPROPERTY(EditAnywhere, Category = "Fade Option", meta = (AllowPrivateAccess = true))
	UMaterialInterface* _fadeMat;

	UPROPERTY(VisibleAnywhere, Category = "Fade Option")
	TArray<UMaterialInterface*> _fadeMaterials;

	UPROPERTY(EditAnywhere, Category = "Fade Option", meta = (AllowPrivateAccess = true))
	float _fadeSpeed;
	UPROPERTY(EditAnywhere, Category = "Fade Option", meta = (AllowPrivateAccess = true))
	float _transparency;

	UPROPERTY(EditAnywhere, Category = "Fade Option", meta = (AllowPrivateAccess = true))
	bool _bIsMeshFade;

	UPROPERTY(VisibleAnywhere, Category = "Fade Option")
	float _fadeToValue;

	UPROPERTY()
	class UStaticMeshComponent* _SM_Static;

	UPROPERTY()
	class USkeletalMeshComponent* _SM_Skeletal;

	UPROPERTY(VisibleAnywhere, Category = "Fade Option")
	TArray<UMaterialInterface*> _staticMaterials;

	UPROPERTY(VisibleAnywhere, Category = "Fade Option")
	TArray<UMaterialInterface*> _skeletalMaterials;



	UPROPERTY(VisibleAnywhere, Category = "Fade Option")
	TArray<UMaterialInstanceDynamic*> _fadeArrayPerMesh;
		
};
