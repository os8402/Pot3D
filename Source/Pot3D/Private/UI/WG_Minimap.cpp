// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WG_Minimap.h"
#include "UI/WG_MinimapIcon.h"
#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"
#include "Creature/UNIT_Player.h"
#include "Materials/MaterialParameterCollection.h"
#include "Materials/MaterialParameterCollectionInstance.h"
#include "Minimap/ACP_MinimapPoint.h"

void UWG_Minimap::NativeConstruct()
{
	Super::NativeConstruct();

	_minimapCollection = GetMaterialCollectionInstance(GetWorld());

	if (_minimapCollection)
	{
		_minimapCollection->SetScalarParameterValue(FName(TEXT("Dimensions")) , _dimensions);
		_minimapCollection->SetScalarParameterValue(FName(TEXT("Zoom")) , _zoom);

	
		UtilsLib::GetTSubClass(&_playerIconClass, TEXT("WidgetBlueprint'/Game/BluePrints/UI/Widget/Template/Minimap/WBP_MinimapIcon_Player.WBP_MinimapIcon_Player_C'"));

		UtilsLib::GetTSubClass(&_otherIconClass, TEXT("WidgetBlueprint'/Game/BluePrints/UI/Widget/Template/Minimap/WBP_MinimapIcon_Other.WBP_MinimapIcon_Other_C'"));

		AddPlayerIcon();

	}


}

void UWG_Minimap::SetMinimapTexture(UTexture2D* newTexture)
{
	if(newTexture == nullptr)
		newTexture = _mapTexture;

	UMaterialInstanceDynamic* mapInstance = _IMG_Map->GetDynamicMaterial();
	if (mapInstance)
		mapInstance->SetTextureParameterValue(FName(TEXT("MapImage")), newTexture);
}


void UWG_Minimap::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (_minimapCollection)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Get Minimap Collection "));
		AUNIT_Player* player = Cast<AUNIT_Player>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

		if (player)
		{
			FVector pos = player->GetActorLocation();
			_minimapCollection->SetScalarParameterValue(FName(TEXT("X")), pos.X);
			_minimapCollection->SetScalarParameterValue(FName(TEXT("Y")), pos.Y);
			_minimapCollection->SetScalarParameterValue(FName(TEXT("Zoom")), _zoom);
			
		}

	}

}


UMaterialParameterCollectionInstance* UWG_Minimap::GetMaterialCollectionInstance(UWorld* world)
{
	if(world == nullptr)
		return nullptr;

	UMaterialParameterCollection* minimapData;

	UtilsLib::GetAssetDynamic<UMaterialParameterCollection>(&minimapData, TEXT("MaterialParameterCollection'/Game/Resources/UI/Minimap/MinimapCollection.MinimapCollection'"));

	if (minimapData)
	{
		return world->GetParameterCollectionInstance(minimapData);
	}

	return nullptr;
}


void UWG_Minimap::AddPlayerIcon()
{

	if (_playerIconClass)
	{
		UWG_MinimapIcon* playerIcon = CreateWidget<UWG_MinimapIcon>(this , _playerIconClass);
		playerIcon->SetOwnerUI(this);


		UOverlaySlot* slot = _OL_MapOverlay->AddChildToOverlay(playerIcon);
		slot->SetHorizontalAlignment(HAlign_Center);
		slot->SetVerticalAlignment(VAlign_Center);
		
	}
}


void UWG_Minimap::AddPointMinimap(UACP_MinimapPoint* minimapPoint, FVector2D size)
{

	if (minimapPoint)
	{

		UTexture2D* iconTexture = minimapPoint->GetIconTexture();

		UWG_MinimapIcon* otherIcon = CreateWidget<UWG_MinimapIcon>(this, _otherIconClass);

		UOverlaySlot* slot = _OL_MapOverlay->AddChildToOverlay(otherIcon);
		slot->SetHorizontalAlignment(HAlign_Center);
		slot->SetVerticalAlignment(VAlign_Center);

		otherIcon->SetOwnerUI(this);
		otherIcon->SetOwnerActor(minimapPoint->GetOwner());
		otherIcon->GetImage()->SetBrushFromTexture(iconTexture);
		otherIcon->GetImage()->SetBrushSize(size);

		_minimapIcons.Add(minimapPoint , otherIcon);
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::FromInt(_minimapIcons.Num()));
		
	}
}



void UWG_Minimap::SetParentFromIcon(UWG_MinimapIcon* minimapIcon)
{

	UOverlaySlot* slot = _OL_MapOverlay->AddChildToOverlay(minimapIcon);
	slot->SetHorizontalAlignment(HAlign_Center);
	slot->SetVerticalAlignment(VAlign_Center);

}

bool UWG_Minimap::RemoveMinimapIcon(UACP_MinimapPoint* point)
{
	if (_minimapIcons.Find(point))
	{
		_minimapIcons[point]->RemoveFromParent();
		_minimapIcons.Remove(point);
		return true;
	}

	return false;
}

