#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UtilsLib.h"
#include "WG_Tooltip_MainBar.generated.h"

struct FSkillData;

UCLASS()
class POT3D_API UWG_Tooltip_MainBar : public UUserWidget
{
	GENERATED_BODY()

public:
	
	void SetTooltipFromData(FSkillData* skillData);

private:
	
	UPROPERTY(meta = (BindWidget))
	class UWG_TitleBar* _WBP_TitleBar;

	UPROPERTY(meta = (BindWidget))
	class UWG_Slot* _WBP_Slot;

	UPROPERTY(meta = (BindWidget) , meta = (MultiLine= true))
	class UTextBlock* _TB_Mana;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* _TB_CoolTime;

	UPROPERTY(meta = (BindWidget) , meta = (MultiLine = true))
	class URichTextBlock* _RTB_Info;

};
