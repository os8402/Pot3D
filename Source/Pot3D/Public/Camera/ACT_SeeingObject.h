// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ACT_SeeingObject.generated.h"

UCLASS()
class POT3D_API AACT_SeeingObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AACT_SeeingObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SetShowSeeingObject(bool bShow);

private:

	UPROPERTY(EditAnywhere, meta =(AllowPrivateAccess=true))
	class UStaticMeshComponent* _MESH_Seeing;
	
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	float _seeingTime;

	bool _bSeeing;

	float _runningTimer;

};
