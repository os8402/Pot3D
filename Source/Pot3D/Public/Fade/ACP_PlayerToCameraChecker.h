// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ACP_PlayerToCameraChecker.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class POT3D_API UACP_PlayerToCameraChecker : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UACP_PlayerToCameraChecker();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	FVector LocationPointBetweenAAndB(FVector A, FVector B, float offSet, float radius);
	void CheckFadeThisMesh();

private:
	
	UPROPERTY(EditAnywhere, Category = "Fade Option")
	float _fadeRadius;
	UPROPERTY(EditAnywhere, Category = "Fade Option")
	float _traceOffsetHeight;
	UPROPERTY(EditAnywhere, Category = "Fade Option")
	float _traceDistanceFromPlayer;
	ETraceTypeQuery _traceChannel;
	UPROPERTY(EditAnywhere, Category = "Fade Option")
	bool _bdebugFade;

	UPROPERTY(EditAnywhere, Category = "Fade Option")
	float _tickInterval;

	UPROPERTY(VisibleAnywhere, Category = "Fade Option")
	TArray<class UACP_FadeThisMesh*> _FTM_currentList;

	UPROPERTY(VisibleAnywhere, Category = "Fade Option")
	TArray<class UACP_FadeThisMesh*> _FTM_removeList;

	UPROPERTY()
	APawn* _player;

	UPROPERTY()
	class APlayerCameraManager* _camera;
		
};
