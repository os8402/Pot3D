#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UEnumHeader.h"
#include "UtilsLib.h"
#include "LocalizationUI.h"
#include "UI/WG_Tooltip.h"
#include "WG_Tooltip_Item.generated.h"

class UOBJ_Item;

UCLASS()
class POT3D_API UWG_Tooltip_Item : public UWG_Tooltip
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "Bonus Stat")
	TSubclassOf<class UWG_BonusStat> _bonusStatClass;

	void RefreshUI(UOBJ_Item* item);
	void Localization(UOBJ_Item* item);

	UPROPERTY(EditAnywhere, Category = "Grade")
	TArray<UTexture2D*> _gradeTextures;
	UPROPERTY(EditAnywhere, Category = "Grade")
	TArray<FLinearColor> _gradeColors;

private:


	UPROPERTY(meta = (BindWidget))
	class UWG_TitleBar* _WBP_TitleBar;

	UPROPERTY(meta = (BindWidget))
	class UWG_Inventory_ItemSlot* _WBP_Inventory_ItemSlot;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* _TB_Grade;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* _TB_Amount;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* _TB_AmountInfo;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* _TB_ItemType;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* _TB_ItemMoreInfo;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* _TB_SellGold;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* _TB_Durability;
	
};
