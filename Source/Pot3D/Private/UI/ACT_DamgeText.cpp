// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ACT_DamgeText.h"
#include "UI/WG_DamgeText.h"
#include "Creature/UNIT_Character.h"
#include "Stat/ACP_StatInfo.h"
#include <Components/WidgetComponent.h>



// Sets default values
AACT_DamgeText::AACT_DamgeText()
{

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	USceneComponent* defalutRoot = CreateDefaultSubobject<USceneComponent>(TEXT("ROOT_COMP"));

	RootComponent = defalutRoot;

	_meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	_meshComp->SetupAttachment(defalutRoot);
	_meshComp->SetRelativeLocation(FVector::ZeroVector);

	_WG_DmgText = CreateDefaultSubobject<UWidgetComponent>(TEXT("DMGTEXT"));
	_WG_DmgText->SetupAttachment(defalutRoot);
	_WG_DmgText->SetWidgetSpace(EWidgetSpace::Screen);
	_WG_DmgText->SetRelativeLocation(FVector(0.f , 0.f, 200.f));

	static ConstructorHelpers::FClassFinder<UUserWidget> UW(TEXT("WidgetBlueprint'/Game/BluePrints/UI/Widget/WBP_DamageText.WBP_DamageText_C'"));
	if (UW.Succeeded())
	{
		_WG_DmgText->SetWidgetClass(UW.Class);
		_WG_DmgText->SetDrawSize(FVector2D(100.f, 100.f));
	}



}

void AACT_DamgeText::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	_WG_DmgText->InitWidget();

}

// Called every frame
void AACT_DamgeText::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	_curTime += DeltaTime;

	if (_curTime >= _destroyTime)
	{
		UWorld* world = GetWorld();
		if (world)
			world->DestroyActor(this);
	}

}

void AACT_DamgeText::UpdateDamage()
{


	int32 colorIndex = (int32)_myOwner->GetStatComp()->GetUnitTypes();

	auto dmgWidget = Cast<UWG_DamgeText>(_WG_DmgText->GetUserWidgetObject());
	dmgWidget->UpdateText(_dmg, _colorList[colorIndex]);
}

