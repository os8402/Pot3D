// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WG_Button.generated.h"

UCLASS()
class POT3D_API UWG_Button : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativePreConstruct() override;
	
public:


	class UButton* GetSlotBtn() {return _BTN_Slot;}





private:
	
	UPROPERTY(meta = (BindWidget))
	class UImage* _IMG_Icon;

	UPROPERTY(meta = (BindWidget))
	class UButton* _BTN_Slot;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* _TB_Name;

	UPROPERTY(EditAnywhere, Category = "Texture" , meta=(AllowPrivateAccess = true))
	class UTexture2D* _texture;
	UPROPERTY(EditAnywhere, Category = "Texture", meta = (AllowPrivateAccess = true))
	FLinearColor _iconColor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	FText _btnName;
};
