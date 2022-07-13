#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WG_GlassBallBar.generated.h"


UCLASS()
class POT3D_API UWG_GlassBallBar : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativePreConstruct() override;

	void BindGauge(class UACP_StatInfo* statComp);

	void UpdateGauge(float value);

private:

	UPROPERTY(EditAnywhere, Category = "Glass Ball" , meta = (AllowPrivateAccess = true))
	UMaterialInterface* _MI_BallMaterial;

	UPROPERTY(meta = (BindWidget))
	class URetainerBox* _RT_Box; 

};
