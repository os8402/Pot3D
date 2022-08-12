#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UtilsLib.h"
#include "GMB_GameMode.generated.h"


UCLASS()
class POT3D_API AGMB_GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGMB_GameMode();

	virtual void PostInitializeComponents() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;





};
