// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ACT_SeeThroughCollision.generated.h"

UCLASS()
class POT3D_API AACT_SeeThroughCollision : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AACT_SeeThroughCollision();

protected:
	
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
	
private:
	void SetShowSeeThroughActor(bool bShow);

	

private:
	
	UPROPERTY()
	class UBoxComponent* _BOX_SeeThroughCol;
	
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TArray<class AACT_SeeThrough*> _seeThroughActors;


};
