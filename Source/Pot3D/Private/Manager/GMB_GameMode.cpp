// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/GMB_GameMode.h"
#include "UI/WG_PublicHud.h"
#include <kismet/GameplayStatics.h>

AGMB_GameMode::AGMB_GameMode()
{
	
}

void AGMB_GameMode::BeginPlay()
{
	Super::BeginPlay();

	/*UtilsLib::GetTSubClass(&_hudClass, TEXT("WidgetBlueprint'/Game/BluePrints/UI/Widget/WBP_PublicHud.WBP_PublicHud_C'"));

	if (_hudClass)
	{
		APlayerController* pc =  UGameplayStatics::GetPlayerController(GetWorld(), 0);

		_hud = CreateWidget<UWG_PublicHud>(pc, _hudClass);
		_hud->AddToViewport();

	
	}*/
}
