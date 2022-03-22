// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/ACT_SeeingCollision.h"
#include "Camera/ACT_SeeingObject.h"
#include "Creature/UNIT_Player.h"
#include <Components/BoxComponent.h>

// Sets default values
AACT_SeeingCollision::AACT_SeeingCollision()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	_BOX_SeeingCol = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX_SeeingCol"));
	RootComponent = _BOX_SeeingCol;
	_BOX_SeeingCol->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));


}

// Called when the game starts or when spawned
void AACT_SeeingCollision::BeginPlay()
{
	Super::BeginPlay();
	
}

void AACT_SeeingCollision::NotifyActorBeginOverlap(AActor* OtherActor)
{
	AUNIT_Player* player = Cast<AUNIT_Player>(OtherActor);

	if (player)
	{
		for (auto seeingActor : _seeingActorLists)
		{
			seeingActor->SetShowSeeingObject(true);
		}

	}
}

void AACT_SeeingCollision::NotifyActorEndOverlap(AActor* OtherActor)
{
	AUNIT_Player* player = Cast<AUNIT_Player>(OtherActor);

	if (player)
	{
		for (auto seeingActor : _seeingActorLists)
		{
			seeingActor->SetShowSeeingObject(false);
		}

	}
}

