// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Equipment/ACP_Equipment.h"
#include "UtilsLib.h"
#include "ACP_Weapon.generated.h"


class UOBJ_Item;
class AUNIT_Character;


UCLASS()
class POT3D_API UACP_Weapon : public UACP_Equipment
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UACP_Weapon();

public:

	class UParticleSystemComponent* GetAttachEffComp() { return _PS_AttachEff; };

	USoundWave* GetDefaultSound() {return _defaultWav;}

private :

	UPROPERTY(VisibleAnywhere, Category = "Effect")
	class UParticleSystemComponent* _PS_AttachEff;

	UPROPERTY(VisibleAnywhere, Category = "Effect")
	class UParticleSystem* _temp_AttachEff;


	// 무기 장착 안 했을 경우 기본적으로 입힐 소리
	UPROPERTY(VisibleAnywhere, Category = "Sound")
	class USoundWave* _defaultWav;

};
