#pragma once

#include "CoreMinimal.h"
#include "UI/WG_Slot.h"
#include "Data/GameDataTable.h"
#include "WG_Skill_Slot.generated.h"


UCLASS()
class POT3D_API UWG_Skill_Slot : public UWG_Slot
{
	GENERATED_BODY()

public:

	virtual void NativePreConstruct() override;


	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual FReply NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void RefreshUI() override;
	void SetSlotLocked(bool bLocked) { _bLocked =bLocked;}

	bool IsLocked() {return _bLocked;} 

private:



	UPROPERTY(meta = (BindWidget))
	class UTextBlock* _TB_SkillLv;

	UPROPERTY()
	class UTexture2D* _TEX_lock;

	bool _bLocked = false;


	UPROPERTY()
	TSubclassOf<UWG_Skill_Slot> _skillSlotClass;
	
};
