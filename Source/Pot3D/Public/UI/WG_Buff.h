#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UtilsLib.h"
#include "UEnumHeader.h"
#include "WG_Buff.generated.h"

class UWG_MainBar;

UCLASS()
class POT3D_API UWG_Buff : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativePreConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void RefreshUI(int32 value , EBuffTypes buffType);

	void SetUIOwner(UWG_MainBar* owner) { _uiOwner = owner;}

	FText GetMyTooltipText() { return _toolTipText;}

private:
	
	UPROPERTY(meta = (BindWidget))
	class UBorder* _BD_Border;
	UPROPERTY(meta = (BindWidget))
	class UImage* _IMG_ItemIcon;

	EBuffTypes _buffType = EBuffTypes::NONE;

	FText _toolTipText;

	UWG_MainBar* _uiOwner;
};
