#include "Minimap/ACP_MinimapPoint.h"
#include "Controller/UNIT_PlayerCT.h"
#include "UI/WG_IngameMain.h"
#include "UI/WG_Minimap.h"

#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
UACP_MinimapPoint::UACP_MinimapPoint()
{

	PrimaryComponentTick.bCanEverTick = false;

	//Default Size;
	_iconSize = FVector2D(32,32);

}


// Called when the game starts
void UACP_MinimapPoint::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle timerHandle;
	float waitTime = 0.1f;

	GetWorld()->GetTimerManager().SetTimer(timerHandle, FTimerDelegate::CreateLambda([&]()
	{

		AUNIT_PlayerCT* pc = Cast<AUNIT_PlayerCT>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		_miniMapUI = pc->GetMainUI()->GetMinimap();

		if (_miniMapUI)
		{
			_miniMapUI->AddPointMinimap(this, _iconSize);
		}


		
	}) ,waitTime, false);

	
}

void UACP_MinimapPoint::RemoveFromUI()
{
	if (_miniMapUI)
	{
		bool bSuccess = _miniMapUI->RemoveMinimapIcon(this);

		if (bSuccess)
		{
			
		}
	}
	
}
