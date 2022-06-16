// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "UNIT_Anim.generated.h"

/**
 * 
 */

DECLARE_MULTICAST_DELEGATE(FOnAttackHit)
UCLASS()
class POT3D_API UUNIT_Anim : public UAnimInstance
{
	GENERATED_BODY()

public:

	virtual void NativeUpdateAnimation(float DeltaSeconds);


public:

	void PlayAttackMontage();
	void JumpToSection(int32 index);
	
	FName GetAttackMontageName(int32 index);

	UFUNCTION()
	void AnimNotify_AttackHit();
	UFUNCTION()
	void AnimNotify_SoundPlay();


public :

	FOnAttackHit& GetOnAttackHit() { return _onAttackHit; }
	void SetDead() { StopAllMontages(.1f); _bDead = true; }


private :

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pawn", Meta = (AllowPrivateAccess = true));
	float _speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pawn", Meta = (AllowPrivateAccess = true));
	bool _bDead;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = true))
	UAnimMontage* _AM_attackMontage;

	FOnAttackHit  _onAttackHit;
};
