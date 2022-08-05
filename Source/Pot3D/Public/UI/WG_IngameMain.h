#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WG_IngameMain.generated.h"

class UWG_Inventory;
class UWG_NamePlate;
class UWG_MainBar;
class UWG_Skill;
class UWG_Minimap;


UCLASS()
class POT3D_API UWG_IngameMain : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativePreConstruct() override;
	void BindStat(class UACP_StatInfo* statComp);
	void BindCreatureInfo();

	void CheckWidgetVisibilty(UUserWidget* widget);

	void OpenInventory();
	void OpenSkill();

public:

	UWG_NamePlate* GetNamePlate() { return _WBP_NamePlate_1; }
	UWG_Inventory* GetInventory() {return _WBP_Inventory;}
	UWG_MainBar* GetMainBar() {return _WBP_MainBar;}
	UWG_Skill* GetSkillPanel() {return _WBP_Skill;}
	UWG_Minimap* GetMinimap() { return _WBP_Minimap; }


private :
	
	

	UPROPERTY(meta = (BindWidget))
	UWG_MainBar* _WBP_MainBar;

	UPROPERTY(meta = (BindWidget))
	UWG_NamePlate* _WBP_NamePlate_1;

	UPROPERTY(meta = (BindWidget))
	UWG_Inventory* _WBP_Inventory;

	UPROPERTY(meta = (BindWidget))
	UWG_Skill* _WBP_Skill;	

	UPROPERTY(meta = (BindWidget))
	UWG_Minimap* _WBP_Minimap;



};
