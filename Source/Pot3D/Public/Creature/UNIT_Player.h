#pragma once

#include "CoreMinimal.h"
#include "UNIT_Character.h"
#include "UNIT_Player.generated.h"


UCLASS()
class POT3D_API AUNIT_Player : public AUNIT_Character
{
	GENERATED_BODY()
public:
	AUNIT_Player();

protected:

	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;

public:

	void SearchActorInfo();
	virtual void AttackAnimCheck() override;
	virtual void SkillAnimCheck() override;

public:

	void GetReward(int32 id);


	TMap<int32, class UACP_Armor*>  GetArmorList() { return _armorList; }


protected:

	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* _SPC_Arm;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* _CAM_Cam;

	UPROPERTY(EditAnywhere, Category = "Pawn")
	float _targetArmLength = 800.f;

private:

	UPROPERTY(VisibleAnywhere, Category = "Armor")
	class UACP_Armor* _ACP_Armor;
	UPROPERTY(VisibleAnywhere, Category = "Armor")
	class UACP_Armor* _ACP_Helmet;
	UPROPERTY(VisibleAnywhere, Category = "Armor")
	class UACP_Armor* _ACP_Pants;
	UPROPERTY(VisibleAnywhere, Category = "Armor")
	class UACP_Armor* _ACP_Boots;

	TMap<int32, UACP_Armor*> _armorList;

private:

	UPROPERTY(VisibleAnyWhere, Category = "FadeMesh")
	class UACP_PlayerToCameraChecker* _ACP_CameraChecker;


};
