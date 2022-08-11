#include "Creature/UNIT_Select.h"
#include <Camera/CameraComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <Components/CapsuleComponent.h>


AUNIT_Select::AUNIT_Select()
{
 
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	_SPC_Arm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPC_ARM"));
	_SPC_Arm->SetupAttachment(GetCapsuleComponent());
	_SPC_Arm->SetUsingAbsoluteRotation(true);
	_SPC_Arm->TargetArmLength = _targetArmLength;
	_SPC_Arm->SetRelativeRotation(FRotator(-60.f, 45.f, 0.f));
	_SPC_Arm->bDoCollisionTest = false;

	GetCapsuleComponent()->SetCollisionProfileName("Player");

	_CAM_Cam = CreateDefaultSubobject<UCameraComponent>(TEXT("CAM"));
	_CAM_Cam->SetupAttachment(_SPC_Arm);
	_CAM_Cam->bUsePawnControlRotation = false;


}
void AUNIT_Select::BeginPlay()
{
	Super::BeginPlay();
	
}


void AUNIT_Select::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


