
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "UNIT_Anim.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnAttackHit)
DECLARE_MULTICAST_DELEGATE(FOnSkillHit)
UCLASS()
class POT3D_API UUNIT_Anim : public UAnimInstance
{
	GENERATED_BODY()

public:

	virtual void NativeUpdateAnimation(float DeltaSeconds);


public:

	void PlayMontageAnim();
	void JumpToSection(FName name);
	
	FName GetAttackMontageName(int32 index);
	FName GetSkillMontageName(FName name);
	int32 GetMaxAttackNum() {return _maxAttackNum;}

	UFUNCTION()
	void AnimNotify_AttackHit();
	UFUNCTION()
	void AnimNotify_SkillHit();
	UFUNCTION()
	void AnimNotify_SoundPlay();


public :

	FOnAttackHit& GetOnAttackHit() { return _onAttackHit; }
	FOnSkillHit& GetOnSkillHit() { return _onSKillHit; }
	void SetDead() { StopAllMontages(.1f); _bDead = true; }


private :

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pawn", Meta = (AllowPrivateAccess = true));
	float _speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pawn", Meta = (AllowPrivateAccess = true));
	bool _bDead;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pawn", Meta = (AllowPrivateAccess = true));
	int32 _maxAttackNum = 2;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = true))
	UAnimMontage* _AM_attackMontage;

	FOnAttackHit  _onAttackHit;
	FOnSkillHit _onSKillHit;
};
