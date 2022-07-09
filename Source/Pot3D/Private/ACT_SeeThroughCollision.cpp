// Fill out your copyright notice in the Description page of Project Settings.


#include "ACT_SeeThroughCollision.h"
#include "Components/BoxComponent.h"
#include "ACT_SeeThrough.h"

#include "Creature/UNIT_Player.h"

// Sets default values
AACT_SeeThroughCollision::AACT_SeeThroughCollision()
{
	_BOX_SeeThroughCol = CreateDefaultSubobject<UBoxComponent>(TEXT("SEE_THROUGH_COLLISION"));
	RootComponent = _BOX_SeeThroughCol;
	_BOX_SeeThroughCol->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
}



void AACT_SeeThroughCollision::NotifyActorBeginOverlap(AActor* OtherActor)
{

	AUNIT_Player* player = Cast<AUNIT_Player>(OtherActor);

	if (player)
		SetShowSeeThroughActor(true);

}

void AACT_SeeThroughCollision::NotifyActorEndOverlap(AActor* OtherActor)
{

	AUNIT_Player* player = Cast<AUNIT_Player>(OtherActor);

	if (player)
		SetShowSeeThroughActor(false);
}

void AACT_SeeThroughCollision::SetShowSeeThroughActor(bool bShow)
{
	for (auto actor : _seeThroughActors)
	{
		actor->SetShowThisActor(bShow);
	}
}
