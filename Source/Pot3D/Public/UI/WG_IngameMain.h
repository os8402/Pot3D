#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WG_IngameMain.generated.h"

class UWG_Inventory;
class UWG_NamePlate;
class UWG_MainBar;

UCLASS()
class POT3D_API UWG_IngameMain : public UUserWidget
{
	GENERATED_BODY()

public:

	void BindStat(class UACP_StatInfo* statComp);
	void BindCreatureInfo();

	void OpenInventory();

public:
	UWG_NamePlate* GetNamePlate() { return _WBP_NamePlate_1; }
	UWG_Inventory* GetInventory() {return _WBP_Inventory;}
	UWG_MainBar* GetMainBar() {return _WBP_MainBar;}

private :
	
	

	UPROPERTY(meta = (BindWidget))
	UWG_MainBar* _WBP_MainBar;

	UPROPERTY(meta = (BindWidget))
	UWG_NamePlate* _WBP_NamePlate_1;

	UPROPERTY(meta = (BindWidget))
	UWG_Inventory* _WBP_Inventory;

};
