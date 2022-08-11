#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WG_Tooltip.generated.h"

UCLASS()
class POT3D_API UWG_Tooltip : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetNameText(FText name);


private :

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* _TB_Name;

};
