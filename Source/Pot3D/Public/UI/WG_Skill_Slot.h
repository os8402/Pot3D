#pragma once

#include "CoreMinimal.h"
#include "UI/WG_Slot.h"
#include "WG_Skill_Slot.generated.h"


UCLASS()
class POT3D_API UWG_Skill_Slot : public UWG_Slot
{
	GENERATED_BODY()

public:

	virtual void NativePreConstruct() override;
	virtual void RefreshUI() override;
	void SetSkillIcon(UTexture2D* texture);

private:
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* _TB_SkillLv;

	UPROPERTY()
	class UTexture2D* _TEX_lock;
	
};
