#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WG_ObjectInfo.generated.h"


UCLASS()
class POT3D_API UWG_ObjectInfo : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void LookObject(FText name);

private:

	UPROPERTY(meta = (BindWidget))
	class UTextBlock * _TB_Name;
};
