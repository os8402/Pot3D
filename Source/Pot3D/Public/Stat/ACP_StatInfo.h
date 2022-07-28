#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UEnumHeader.h"
#include "Manager/GI_GmInst.h" 
#include "Data/GameDataTable.h"
#include "ACP_StatInfo.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHpChanged)
DECLARE_MULTICAST_DELEGATE(FOnMpChanged)
DECLARE_MULTICAST_DELEGATE(FOnUnitDied)

class UOBJ_Item;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class POT3D_API UACP_StatInfo : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UACP_StatInfo();

protected:

	virtual void InitializeComponent() override;

public:
	void OnAttacked(int32 dmg);


public:

	void SetCharacterId(int32 id);
	void SetUnitTypes(EUnitTypes type) { _unitType = type; }

	void SetHp(int32 newHp);
	void SetMp(int32 newMp);
	void SetExp(int32 exp);


	void SetMaxHp(int32 maxhp) { _maxHp += maxhp;}
	void SetMaxMp(int32 maxMp) { _maxMp += maxMp; }


	int32 GetCharacterId() { return _chrId; }
	FString GetChracterName() { return _chrName;}
	int32 GetHp() { return _hp; }
	int32 GetMaxHp() { return _maxHp; }
	float GetHpRatio() { return  _hp / (float)_maxHp; }
	int32 GetMp() { return _mp; }
	int32 GetMaxMp() { return _maxMp; }
	float GetMpRatio() { return  _mp / (float)_maxMp; }
	int32 GetLevel() { return _level; }
	EUnitJobs GetJob() { return _job; }
	EUnitTypes GetUnitTypes() { return _unitType; }

	int32 GetMinAttack() { return _minAtk; }
	int32 GetMaxAttack() { return _maxAtk; }
	int32 GetDefence() { return _defence; }
	int32 GetResilience() { return _resilience; }
	int32 GetStrength() { return _strength; }
	int32 GetDexterity() { return _dexterity; }
	int32 GetIntelligence() { return _intelligence; }
	int32 GetLuck() { return _luck; }

	TMap<int32, int32> GetBonuStats(){return _bonusStats;}

	int32 GetBonusMinAttck() {return _bonusMinAtk; }
	int32 GetBonusMaxAttck() {return _bonusMaxAtk; }
	int32 GetBonusDefece() {return _bonusDef; }
	int32 GetBonusResilience() {return _bonusRes; }

	FOnHpChanged& GetOnHpChanged() { return _onHpChanged; }
	FOnMpChanged& GetOnMpChanged() { return _onMpChanged; }

	FOnUnitDied& GetOnUnitDied() { return _onUnitDied; }

public:
	
	void RefreshStat(const FStatData statData , const TMap<int32, int32> bonusStats);



private:


	UPROPERTY(VisibleAnywhere, Category = "Stat", meta = (AllowPrivateAccess = true))
	int32 _chrId;
	UPROPERTY(VisibleAnywhere, Category = "Stat", meta = (AllowPrivateAccess = true))
	FString _chrName;
	UPROPERTY(VisibleAnywhere, Category = "Stat", meta = (AllowPrivateAccess = true))
	int32 _level;
	UPROPERTY(VisibleAnywhere, Category = "Stat", meta = (AllowPrivateAccess = true))
	EUnitJobs _job;
	UPROPERTY(VisibleAnywhere, Category = "Stat", meta = (AllowPrivateAccess = true))
	EUnitTypes _unitType;

	UPROPERTY(VisibleAnywhere, Category = "Stat", meta = (AllowPrivateAccess = true))
	int32 _hp;
	UPROPERTY(VisibleAnywhere, Category = "Stat", meta = (AllowPrivateAccess = true))
	int32 _mp;
	UPROPERTY(VisibleAnywhere, Category = "Stat", meta = (AllowPrivateAccess = true))
	int32 _maxHp;
	UPROPERTY(VisibleAnywhere, Category = "Stat", meta = (AllowPrivateAccess = true))
	int32 _maxMp;

	UPROPERTY(VisibleAnywhere, Category = "Stat", meta = (AllowPrivateAccess = true))
	int32 _minAtk;
	UPROPERTY(VisibleAnywhere, Category = "Stat", meta = (AllowPrivateAccess = true))
	int32 _maxAtk;
	UPROPERTY(VisibleAnywhere, Category = "Stat", meta = (AllowPrivateAccess = true))
	int32 _defence;
	UPROPERTY(VisibleAnywhere, Category = "Stat", meta = (AllowPrivateAccess = true))
	int32 _resilience;
	UPROPERTY(VisibleAnywhere, Category = "Stat", meta = (AllowPrivateAccess = true))
	int32 _strength;
	UPROPERTY(VisibleAnywhere, Category = "Stat", meta = (AllowPrivateAccess = true))
	int32 _dexterity;
	UPROPERTY(VisibleAnywhere, Category = "Stat", meta = (AllowPrivateAccess = true))
	int32 _intelligence;
	UPROPERTY(VisibleAnywhere, Category = "Stat", meta = (AllowPrivateAccess = true))
	int32 _luck;


	UPROPERTY()
	TMap<int32, int32> _bonusStats;

	UPROPERTY()
	int32 _bonusMinAtk;
	UPROPERTY()
	int32 _bonusMaxAtk;
	UPROPERTY()
	int32 _bonusDef;
	UPROPERTY()
	int32 _bonusRes;


	FOnHpChanged _onHpChanged;
	FOnMpChanged _onMpChanged;
	FOnUnitDied _onUnitDied;

};
