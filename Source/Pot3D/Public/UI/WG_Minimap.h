#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UtilsLib.h"
#include "WG_Minimap.generated.h"

class UMaterialParameterCollectionInstance;
class UWG_MinimapIcon;
class UACP_MinimapPoint;

UCLASS()
class POT3D_API UWG_Minimap : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;


public:
	
	void AddPlayerIcon();
	void AddPointMinimap(class UACP_MinimapPoint* minimapPoint);

	UMaterialParameterCollectionInstance* GetMaterialCollectionInstance(UWorld* world);

	float GetDimensions() {return _dimensions;}
	float GetZoom() {return _zoom;}
	UImage* GetMapImage() {return _IMG_Map;}

	void SetParentFromIcon(UWG_MinimapIcon* minimapIcon);

	bool RemoveMinimapIcon(UACP_MinimapPoint* point);


private:

	UPROPERTY(meta = (BindWidget))
	class UImage* _IMG_Map;
	UPROPERTY(meta = (BindWidget))
	class UOverlay* _OL_MapOverlay;


	UPROPERTY(EditAnywhere , Category = "Minimap" , meta = (AllowPrivateAccess = true))
	float _dimensions;
	UPROPERTY(EditAnywhere, Category = "Minimap", meta = (AllowPrivateAccess = true))
	float _zoom;
	UPROPERTY(EditAnywhere, Category = "Minimap", meta = (AllowPrivateAccess = true))
	UTexture2D* _mapTexture;

	UPROPERTY()
	UMaterialParameterCollectionInstance* _minimapCollection;

	UPROPERTY()
	TSubclassOf<UWG_MinimapIcon> _playerIconClass;
	UPROPERTY()
	TSubclassOf<UWG_MinimapIcon> _otherIconClass;

	TMap< UACP_MinimapPoint*, UWG_MinimapIcon*> _minimapIcons;
};
