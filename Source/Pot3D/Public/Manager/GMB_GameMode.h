#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UtilsLib.h"
#include "GMB_GameMode.generated.h"

class UWG_PublicHud;

UCLASS()
class POT3D_API AGMB_GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGMB_GameMode();

	virtual void BeginPlay() override;

public:

	

private:

	UPROPERTY()
	TSubclassOf<UWG_PublicHud> _hudClass;

	UWG_PublicHud* _hud;
	
};
