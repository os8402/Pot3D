// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/ACP_SKillInfo_Paladin.h"
#include "Kismet/KismetSystemLibrary.h"
#include <Kismet/GameplayStatics.h>


#include "Creature/UNIT_Player.h"


void UACP_SKillInfo_Paladin::InitializeComponent()
{
	Super::InitializeComponent();

}

void UACP_SKillInfo_Paladin::UseActiveSkill(FName name)
{
	Super::UseActiveSkill(name);

	FString skillName = FString::Printf(TEXT("Skill_%s"), *name.ToString());

	if (SKILL_GOT_MACE == skillName)
		SKill_GotMace();
	else if (SKILL_GOT_BLESS == skillName)
		SKill_GotBless();
	else if (SKILL_EARTH_QUAKE == skillName)
		SKill_EarthQuake();
	else if (SKILL_RUSH == skillName)
		SKill_Rush();
	else
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Paladin Skill Not Found"));
}



void UACP_SKillInfo_Paladin::RangeAttackSkill(int32 attackRange)
{
	Super::RangeAttackSkill(attackRange);

	AUNIT_Player* player = Cast<AUNIT_Player>(GetOwner());
	FVector pos = player->GetActorLocation();

	TArray<AActor*> ignoreActors;
	TArray<AActor*> outActors;

	ignoreActors.Add(player);
	
	bool result =  GetOverlapSphereUnit(pos , attackRange , ignoreActors , outActors);

	if(result == false)
		return;

	for (const auto& actor : outActors)
	{
		AUNIT_Character* character = Cast<AUNIT_Character>(actor);

		if (character == nullptr)
			continue;

		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Orange,
			FString::Printf(TEXT("hit : %s"), *actor->GetName()));

		_skillTargetEnemys.Add(character);

	}
	
}	



//½ÅÀÇÃ¶Åð
void UACP_SKillInfo_Paladin::SKill_GotMace()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Skill : Got Mace"));

	RangeAttackSkill(300.f);
	
}

void UACP_SKillInfo_Paladin::SKill_GotBless()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Skill : Got Bless"));

	AUNIT_Player* player = Cast<AUNIT_Player>(GetOwner());

	_skillTargetEnemys.Add(player);

}

void UACP_SKillInfo_Paladin::SKill_EarthQuake()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Skill : EarthQuake"));

	RangeAttackSkill(500.f);

}	

void UACP_SKillInfo_Paladin::SKill_Rush()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Skill : Rush"));

	AUNIT_Character* target =  GetNearDistanceTarget(800.f);

}

AUNIT_Character* UACP_SKillInfo_Paladin::GetNearDistanceTarget(float radius)
{
	AUNIT_Player* player = Cast<AUNIT_Player>(GetOwner());
	FVector pos = player->GetActorLocation();

	TArray<AActor*> ignoreActors;
	TArray<AActor*> outActors;

	ignoreActors.Add(player);

	bool result = GetOverlapSphereUnit(pos, radius, ignoreActors, outActors);

	if (result == false)
		return nullptr;

	float maxDist = 1e9;
	AUNIT_Character* target = nullptr;


	for (const auto& actor : outActors)
	{
		AUNIT_Character* character = Cast<AUNIT_Character>(actor);

		if (character == nullptr)
			continue;

		FVector charPos = character->GetActorLocation();

		float const dist = FVector::Dist(pos, charPos);


		if (dist < maxDist)
		{
			maxDist = dist;
			target = character;

			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Orange,
				FString::Printf(TEXT("near Target %s : %f"), *actor->GetName(), maxDist));
		}
	}

	return target;
}