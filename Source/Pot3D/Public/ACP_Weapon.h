// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ACP_Weapon.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class POT3D_API UACP_Weapon : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UACP_Weapon();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


public:

	class UParticleSystemComponent* GetAttachEffComp() { return _PS_AttachEff; };

	class UAudioComponent* GetAudioComp() { return _Audio_Comp; }
	void SoundPlay(int32 index);


private:
	UPROPERTY(VisibleAnywhere, Category = "Audio")
	class UAudioComponent* _Audio_Comp;

	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	TArray<class USoundCue*> _SOUND_WEPAON_Lists;

	UPROPERTY(VisibleAnywhere, Category = "Effect")
	class UParticleSystemComponent* _PS_AttachEff;


	UPROPERTY(VisibleAnywhere, Category = "Effect")
	class UParticleSystem* _temp_AttachEff;
		
};
