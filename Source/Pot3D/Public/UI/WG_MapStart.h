#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WG_MapStart.generated.h"


UCLASS()
class POT3D_API UWG_MapStart : public UUserWidget
{
	GENERATED_BODY()

public:
	
	void UpdateText(FText text);
	

private : 
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* _TB_MapName;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* _WA_Fade;
};
