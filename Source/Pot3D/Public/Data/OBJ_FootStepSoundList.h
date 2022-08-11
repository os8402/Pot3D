#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "OBJ_FootStepSoundList.generated.h"

UCLASS(Blueprintable)
class POT3D_API UOBJ_FootStepSoundList : public UObject
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sound, Meta = (AllowPrivateAccess = true))
	TMap<FString, class USoundBase*> m_pSoundList;

public:
	class USoundBase* GetSound(FString sSoundName);
	int GetSoundListNum() { return m_pSoundList.Num(); }
	
};
