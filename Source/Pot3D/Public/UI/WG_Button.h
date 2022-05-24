// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WG_Button.generated.h"

/**
 * 
 */
UCLASS()
class POT3D_API UWG_Button : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativePreConstruct() override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	FText _btnName; 

private:


	UPROPERTY(meta = (BindWidget))
	class UTextBlock* _TB_Name;
};
