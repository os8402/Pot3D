// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/GMB_GameMode.h"
#include <kismet/GameplayStatics.h>
#include "Manager/PS_PlayerState.h"


AGMB_GameMode::AGMB_GameMode()
{
	PlayerStateClass = APS_PlayerState::StaticClass();	
}


void AGMB_GameMode::PostInitializeComponents()
{
	Super::PostInitializeComponents();


}

void AGMB_GameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	APS_PlayerState* ps = Cast<APS_PlayerState>(NewPlayer->PlayerState);
	ps->LoadDataFromPlayer();

	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Load From Data"));

}
