// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WG_PublicHud.generated.h"


class UWG_Minimap;

UCLASS()
class POT3D_API UWG_PublicHud : public UUserWidget
{
	GENERATED_BODY()

public:
	UWG_Minimap* GetMinimap() { return _WBP_Minimap; }
private:

	UPROPERTY(meta = (BindWidget))
	UWG_Minimap* _WBP_Minimap;
	
};
