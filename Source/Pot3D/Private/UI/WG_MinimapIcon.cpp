// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WG_MinimapIcon.h"
#include "UI/WG_Minimap.h"
#include "Creature/UNIT_Player.h"
#include <kismet/GameplayStatics.h>
#include <Kismet/KismetMathLibrary.h>
#include <Kismet/KismetMathLibrary.h>

void UWG_MinimapIcon::NativePreConstruct()
{
	Super::NativePreConstruct();


}



void UWG_MinimapIcon::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (_bIsPlayer)
	{
		TickPlayerIconRotation();

	}
	else
	{
		
		TickOtherIconRogic();
	}


}

float UWG_MinimapIcon::FindAngle(FVector2D A, FVector2D B)
{
	float x = A.X - B.X;
	float y = A.Y - B.Y;

	return 	UKismetMathLibrary::DegAtan2(y, x);;
}

FVector2D UWG_MinimapIcon::FindCoord(float radius, float degrees)
{
	radius = UKismetMathLibrary::Clamp(radius , 0, 160.f);

	float cosDegree = UKismetMathLibrary::DegCos(degrees);
	float sinDegree = UKismetMathLibrary::DegSin(degrees);
	float x = (sinDegree * radius);
	float y = (cosDegree * radius);


	return FVector2D(x,y);
}

void UWG_MinimapIcon::TickPlayerIconRotation()
{
	AUNIT_Player* player = Cast<AUNIT_Player>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (player)
	{
		float z = player->GetMesh()->GetComponentRotation().Yaw;
		SetRenderTransformAngle(z);
	}

}

void UWG_MinimapIcon::TickOtherIconRogic()
{	
//	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::Printf(TEXT("Check Start")));

	auto player =  UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	
	FVector playerPos = player->GetActorLocation();
	FVector ownerPos = _ownerActor->GetActorLocation();

	float x = (ownerPos.X - playerPos.X) ;
	float y = -(ownerPos.Y - playerPos.Y);

	float zoom = _ownerUI->GetZoom();
	float dimensions = _ownerUI->GetDimensions();

	FVector2D mapSize = _ownerUI->GetMapImage()->GetDesiredSize();

	dimensions /= mapSize.X;

	float calc = (zoom * dimensions);

	x /= calc;
	y /= calc;

	FVector2D calcPos = FVector2D(x,y);

	float posLength = calcPos.Size();

	float angle = FindAngle(FVector2D::ZeroVector , calcPos);
	
	FVector2D coord = FindCoord(posLength , angle);

	SetRenderTranslation(coord);

	float coordLength = coord.Size();

	

	//¸Ê ¹þ¾î³ª¸é ¾È º¸ÀÌ°Ô
	if (coordLength >= 155.f)
		_IMG_Icon->SetVisibility(ESlateVisibility::Hidden);
	else
		_IMG_Icon->SetVisibility(ESlateVisibility::Visible);


}


