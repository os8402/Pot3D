// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ACT_SeeingCollision.generated.h"

UCLASS()
class POT3D_API AACT_SeeingCollision : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AACT_SeeingCollision();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

private:

	UPROPERTY()
	class UBoxComponent* _BOX_SeeingCol;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	TArray<class AACT_SeeingObject*> _seeingActorLists;

};
