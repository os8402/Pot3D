// Fill out your copyright notice in the Description page of Project Settings.


#include "Fade/ACP_PlayerToCameraChecker.h"
#include <Kismet/GameplayStatics.h>
#include "Fade/ACP_FadeThisMesh.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Camera/PlayerCameraManager.h"
#include "Controller/UNIT_PlayerCT.h"

UACP_PlayerToCameraChecker::UACP_PlayerToCameraChecker()
{

	PrimaryComponentTick.bCanEverTick = true;

	_fadeRadius = 50.f;
	_traceOffsetHeight = 0.f;
	_traceDistanceFromPlayer = 0;
	_tickInterval = 0.09f;
	_traceChannel = TraceTypeQuery2; // CAMERA:
	_bdebugFade = false;

}


// Called when the game starts
void UACP_PlayerToCameraChecker::BeginPlay()
{
	Super::BeginPlay();

	SetComponentTickInterval(_tickInterval);

	_player = Cast<APawn>(GetOwner());

	auto pc = Cast<AUNIT_PlayerCT>(_player->GetController());

	if (pc)
	{
		_camera = pc->PlayerCameraManager;
	}



}


// Called every frame
void UACP_PlayerToCameraChecker::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CheckFadeThisMesh();
}

FVector UACP_PlayerToCameraChecker::LocationPointBetweenAAndB(FVector A, FVector B, float offSet, float radius)
{
	FVector dir = (A - B).GetSafeNormal();

	int32 sum = offSet + radius;

	dir *= sum;

	return A + dir;
}

void UACP_PlayerToCameraChecker::CheckFadeThisMesh()
{

	FVector playerPos = _player->GetActorLocation();
	FVector cameraPos = _camera->GetCameraLocation();

	FVector calcPos = LocationPointBetweenAAndB(playerPos, cameraPos,
		_traceDistanceFromPlayer, _fadeRadius);

	TArray<AActor*> ignoreActors; // 무시할 액터들.
	TArray<FHitResult> outHits;

	EDrawDebugTrace::Type debugTrace = _bdebugFade ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None;


	bool result = UKismetSystemLibrary::SphereTraceMulti
	(
		GetWorld(),
		cameraPos,
		calcPos + _traceOffsetHeight,
		_fadeRadius,
		_traceChannel,
		true,
		ignoreActors,
		debugTrace,
		outHits,
		true

	);

	if (result)
	{
		TArray<UACP_FadeThisMesh*> FTM_update;

		UE_LOG(LogTemp, Log, TEXT("Hit Length : %d"), outHits.Num());

		for (auto& hit : outHits)
		{
			FString name;
			hit.Actor->GetName(name);

			UE_LOG(LogTemp, Log, TEXT("Fade to Object : %s"), *name);


			//TODO : ToFadeThisActor 추가 후에 진행
			auto fadeMesh = Cast<UACP_FadeThisMesh>
				(hit.Actor->GetComponentByClass(UACP_FadeThisMesh::StaticClass()));


			if (fadeMesh == nullptr)
				continue;
		
			FTM_update.Add(fadeMesh);

		}
	
		bool bEqual = FTM_update == _FTM_currentList;

		if (bEqual == false)
		{

			for (auto ftm : FTM_update)
			{
				if (_FTM_currentList.Contains(ftm))
					continue;

				ftm->FadeStart();
				_FTM_currentList.Add(ftm);
			}

			for (auto cur : _FTM_currentList)
			{
				if (FTM_update.Contains(cur))
					continue;

				_FTM_removeList.Add(cur);

			}

			for (auto rmv : _FTM_removeList)
			{
				rmv->FadeEnd();
				_FTM_currentList.Remove(rmv);
			}


			_FTM_removeList.Empty();
		}

	}


}
