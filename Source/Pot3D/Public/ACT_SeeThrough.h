// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ACT_SeeThrough.generated.h"

UCLASS()
class POT3D_API AACT_SeeThrough : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AACT_SeeThrough();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void SetShowThisActor(bool bShow);

private :
	
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* _MESH_SeeThrough;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float _seeThroughTime;
	
	bool _bSeeing;

	float _runningTime;


};
