#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WG_MinimapIcon.generated.h"



class UWG_Minimap;
class UACP_MinimapPoint;

UCLASS()
class POT3D_API UWG_MinimapIcon : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
public:

	float FindAngle(FVector2D A , FVector2D B);
	FVector2D FindCoord(float radius , float degrees);

	void TickPlayerIconRotation();
	void TickOtherIconRogic();

	UImage* GetImage(){ return _IMG_Icon;}
	void SetOwnerActor(AActor* owner) {_ownerActor = owner;}
	void SetOwnerUI(UWG_Minimap* owner ) { _ownerUI = owner;}
	void SetMinimapPointActor(UACP_MinimapPoint* minimapPoint) { _minimapPoint = minimapPoint;}

public:


private:

	UPROPERTY(EditAnywhere, Category = "Minimap", meta = (AllowPrivateAccess = true))
	bool _bIsPlayer;

	UPROPERTY(meta = (BindWidget))
	class UImage* _IMG_Icon;



	UPROPERTY()
	AActor* _ownerActor; 

	UWG_Minimap* _ownerUI;
	UACP_MinimapPoint* _minimapPoint;
};
