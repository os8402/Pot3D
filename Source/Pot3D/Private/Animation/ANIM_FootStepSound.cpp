#include "Animation/ANIM_FootStepSound.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimSequenceBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Sound/SoundBase.h"
#include "PhysicalMaterials/PhysicalMaterial.h"

#include "Data/OBJ_FootStepSoundList.h"


UANIM_FootStepSound::UANIM_FootStepSound() : Super()
{
	m_fCheckDistance = 10.0f;
	m_bSoundAttach = false;
	m_bShowDebugLine = false;

#if WITH_EDITORONLY_DATA
	NotifyColor = FColor(192, 255, 99, 255);
#endif 
}

void UANIM_FootStepSound::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	FootStep(MeshComp);
}

void UANIM_FootStepSound::FootStep(USkeletalMeshComponent* MeshComp)
{
	if (m_pRef_SoundList == nullptr) return;
	if (m_pSoundList == nullptr) m_pSoundList = m_pRef_SoundList->GetDefaultObject<UOBJ_FootStepSoundList>();
	if (m_pSoundList == nullptr) return;


	const FTransform pMeshTransform = MeshComp->GetSocketTransform(SocketName);

	FVector vLineTrace_Start = pMeshTransform.GetLocation() + m_vLocationOffset;
	FVector vLineTrace_End = pMeshTransform.GetLocation() - FVector::UpVector * m_fCheckDistance;

	FHitResult pHitResult;
	TArray<AActor*> pIgnore;
	pIgnore.Add(MeshComp->GetOwner());

	bool bDebug = false;
	bDebug = m_bShowDebugLine;

	EDrawDebugTrace::Type eDebug = EDrawDebugTrace::None;
	if (bDebug == true) eDebug = EDrawDebugTrace::ForDuration;

	bool bResult = UKismetSystemLibrary::LineTraceSingle(MeshComp->GetWorld(), vLineTrace_Start, vLineTrace_End,
		UEngineTypes::ConvertToTraceType(ECC_WorldStatic), true, pIgnore, eDebug, pHitResult, true);

	if (bResult == true)
	{
		if (pHitResult.GetActor() == nullptr) return;

		USoundBase* pSound = m_pSoundList->GetSound(pHitResult.PhysMaterial->GetName());
		if (pSound == nullptr) return;

		if (pSound->IsLooping() == true)
		{
			UE_LOG(LogTemp, Warning, TEXT("PMBFootStepSound : This Notify Sound must be turn off Loop"));
			return;
		}

		if (m_bSoundAttach)
		{
			UGameplayStatics::SpawnSoundAttached(pSound, MeshComp, SocketName, FVector(ForceInit), EAttachLocation::SnapToTarget, false, m_fVolumeMultiplier, m_fPitchMultiplier);
		}
		else
		{
			UGameplayStatics::PlaySoundAtLocation(MeshComp->GetWorld(), pSound, MeshComp->GetComponentLocation(), m_fVolumeMultiplier, m_fPitchMultiplier);
		}
	}
}
