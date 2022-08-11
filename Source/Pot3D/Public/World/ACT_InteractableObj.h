#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UtilsLib.h"
#include "UEnumHeader.h"
#include "ACT_InteractableObj.generated.h"

UCLASS()
class POT3D_API AACT_InteractableObj : public AActor
{
	GENERATED_BODY()
	
public:	

	AACT_InteractableObj();

protected:

	virtual void PostInitializeComponents() override;

public:
	void SetOutline(bool on);

	void ExecuteInteractableMethod();
	void ExecuteWarp();
	void ExecuteUI();


	EInteractable GetInteractableType() { return _interactableType;}

private:
	
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* _BOX_Trigger;

	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* _WC_Info;


	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* _MESH_Static;
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* _MESH_Skeletal;

	UPROPERTY(EditAnywhere , Category = "UI" , meta =(AllowPrivateAccess = true))
	FText _objName;

	UPROPERTY(EditAnywhere, Category = "Interactable", meta = (AllowPrivateAccess = true))
	EInteractable _interactableType; 

	//이름으로 구별해서 상호작용
	UPROPERTY(EditAnywhere, Category = "Interactable", meta = (AllowPrivateAccess = true))
	FString _interactableStr;


	UPROPERTY(VisibleAnywhere, Category = "UI")
	class UACP_MinimapPoint* _ACP_MinimapPoint;
};
