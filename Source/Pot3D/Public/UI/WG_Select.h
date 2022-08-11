// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WG_Select.generated.h"

class UWG_Button;

UCLASS()
class POT3D_API UWG_Select : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void StartGame();
	
private:

	UPROPERTY(meta = (BindWidget))
	UWG_Button* _BTN_GameStart;
	
};
