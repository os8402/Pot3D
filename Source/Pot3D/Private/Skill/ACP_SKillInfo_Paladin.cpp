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
	FString skillName = FString::Printf(TEXT("Skill_%s"), *name.ToString());

	if (SKILL_GOT_MACE == skillName)
		SKill_GotMace();
	else if (SKILL_GOT_BLESS == skillName)
		SKill_GotBless();
	else if (SKILL_GOT_EARTH_CRUSH == skillName)
		SKill_EarthCrush();
	else if (SKILL_GOT_BONE_CRUSH == skillName)
		SKill_BoneCrush();
	else
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Paladin Skill Not Found"));
}

//신의철퇴
void UACP_SKillInfo_Paladin::SKill_GotMace()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Skill : Got Mace"));

	AUNIT_Player* player = Cast<AUNIT_Player>(GetOwner());

	FVector startPos = player->GetActorLocation();
	FVector endPos = player->GetActorLocation();


	//임시용 나중에 스킬 데이터에서 배껴서 해야함
	float attackRange = 300.f;

	TArray<TEnumAsByte<EObjectTypeQuery>> objectTypes;
	TArray<AActor*> ignoreActors; // 무시할 액터들.
	TArray<AActor*> outActors;


	objectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));

	ignoreActors.Add(player);

	//EDrawDebugTrace::Type debugTrace = _bdebugFade ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None;
	EDrawDebugTrace::Type debugTrace = EDrawDebugTrace::ForDuration;

	bool result = UKismetSystemLibrary::SphereOverlapActors
	(
		GetWorld(),
		startPos,
		attackRange,
		objectTypes,
		nullptr,
		ignoreActors,
		outActors
	);


	if (result)
	{
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
	
}

void UACP_SKillInfo_Paladin::SKill_GotBless()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Skill : Got Bless"));
}

void UACP_SKillInfo_Paladin::SKill_EarthCrush()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Skill : Earth Crush"));
}	

void UACP_SKillInfo_Paladin::SKill_BoneCrush()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Skill : Bone Crush"));
}
