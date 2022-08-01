// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UtilsLib.h"
#include "ACT_DamgeText.generated.h"

UCLASS()
class POT3D_API AACT_DamgeText : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AACT_DamgeText();

protected:
	// Called when the game starts or when spawned
	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void UpdateDamage(int32 value , ESpawnTextTypes spawnType);


private:

	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* _WG_DmgText;
	
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* _meshComp;


	float _curTime = 0.0f;
	float _destroyTime = 1.f;

	TArray<FLinearColor> _colorList = { FLinearColor::Red , FLinearColor::Yellow,  FLinearColor::Green };
	


};
