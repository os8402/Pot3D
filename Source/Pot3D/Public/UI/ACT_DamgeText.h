// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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

	void UpdateDamage();
	void SetDamage(int32 dmg) { _dmg = dmg; }
	void SetMyOwner(class AUNIT_Character* owner) { _myOwner = owner; }

private:

	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* _WG_DmgText;
	
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* _meshComp;


	float _curTime = 0.0f;
	float _destroyTime = 1.f;

	int32 _dmg = 0;

	TArray<FLinearColor> _colorList = { FLinearColor::Yellow, FLinearColor::Red,  FLinearColor::Blue };
	
	UPROPERTY(VisibleAnywhere)
	class AUNIT_Character* _myOwner;

};
