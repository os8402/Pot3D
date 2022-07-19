#pragma once

#include "CoreMinimal.h"
#include "UI/WG_Slot.h"
#include "UtilsLib.h"
#include "WG_MainBar_Slot.generated.h"


UCLASS()
class POT3D_API UWG_MainBar_Slot : public UWG_Slot
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct() override;
	void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	FReply NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;


	virtual void RefreshUI() override;


private:

	UPROPERTY(meta = (BindWidget))
	class UImage* _IMG_CoolTime;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* _TB_SlotIndex;

	UMaterialInstanceDynamic* _MID_coolTime;

	UPROPERTY(EditAnywhere, Category = "CoolTime" , meta=(AllowPrivateAccess = true))
	float _coolTimePercent;

	
	
};
