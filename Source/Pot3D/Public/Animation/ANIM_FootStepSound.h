#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "ANIM_FootStepSound.generated.h"


UCLASS()
class POT3D_API UANIM_FootStepSound : public UAnimNotify
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimNotify", meta = (DisplayName = "PMB Sound List"))
	TSubclassOf<class UOBJ_FootStepSoundList> m_pRef_SoundList;

	UPROPERTY()
	class UOBJ_FootStepSoundList* m_pSoundList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimNotify", meta = (ExposeOnSpawn = true))
	float m_fVolumeMultiplier = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimNotify", meta = (ExposeOnSpawn = true))
	float m_fPitchMultiplier = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimNotify")
	uint32 m_bSoundAttach : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimNotify")
	FVector m_vLocationOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimNotify")
	float m_fCheckDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimNotify")
	FName SocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimNotify")
	uint32 m_bShowDebugLine : 1;

public:
	UANIM_FootStepSound();
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

public:
	void FootStep(USkeletalMeshComponent* MeshComp);
};
	
