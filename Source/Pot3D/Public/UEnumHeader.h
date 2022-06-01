// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"



UENUM(BlueprintType)
enum class EUnitStates : uint8
{
	IDLE UMETA(DisplayName = "IDLE"),
	MOVE UMETA(DisplayName = "MOVE"),
	ATTACK UMETA(DisplayName = "ATTACK"),
	DEAD UMETA(DisplayName = "DEAD")
};

UENUM(BlueprintType)
enum class EUnitTypes : uint8
{
	PLAYER UMETA(DisplayName = "PLAYER"),
	MONSTER UMETA(DisplayName = "MONSTER"),
	PROJECTILE UMETA(DisplayName = "PROJECTILE"),
	NPC  UMETA(DisplayName = "NPC"),

	END
};

UENUM(BlueprintType)
enum class EUnitJobs : uint8
{
	WARRIOR UMETA(DisplayName = "WARRIOR"),
	ARCHER UMETA(DisplayName = "ARCHER"),
	MAGE UMETA(DisplayName = "MAGE"),
	END
};

UENUM(BlueprintType)
enum class ESoundTypes : uint8
{
	CHARACTER UMETA(DisplayName = "CHARACTER"),
	WEAPON UMETA(DisplayName = "WEAPON"),
	//SKILL UMETA(DisplayName = "SKILL"),
	BGM UMETA(DisplayName = "BGM"),

	END
};


UENUM(BlueprintType)
enum class ECharacterSounds : uint8
{
	NORMAL UMETA(DisplayName = "NORMAL"),
	SKILL01 UMETA(DisplayName = "SKILL01"),
	SKILL02 UMETA(DisplayName = "SKILL02"),
	DEAD UMETA(DisplayName = "DEAD"),

	END
};

UENUM(BlueprintType)
enum class EWeaponSounds : uint8
{
	NORMAL UMETA(DisplayName = "NORMAL"),
	SKILL01 UMETA(DisplayName = "SKILL01"),
	SKILL02 UMETA(DisplayName = "SKILL02"),

	END
};

UENUM(BlueprintType)
enum class ETableDatas : uint8
{
	UNIT  = 0 UMETA(DisplayName = "UNIT"), 
	MONSTER UMETA(DisplayName = "MONSTER"),
	ITEM UMETA(DisplayName = "ITEM"),


	END
};

UENUM(BlueprintType)
enum class EEquipmentTypes : uint8
{
	NONE = 0 UMETA(DisplayName = "NONE"),
	WEAPON UMETA(DisplayName = "WEAPON"),
	HELMET UMETA(DisplayName = "HELMET"),
	ARMOR UMETA(DisplayName = "ARMOR"),
	PANTS UMETA(DisplayName = "PANTS"),
	BOOTS UMETA(DisplayName = "BOOTS"),

	END
};

UENUM(BlueprintType)
enum class EItemTypes : uint8
{
	NONE = 0 UMETA(DisplayName = "NONE"),
	EQUIPMENT UMETA(DisplayName = "EQUIPMENT"),
	CONSUMABLE UMETA(DisplayName = "CONSUMABLE"),
	JEWEL UMETA(DisplayName = "JEWEL"),
	GOLD UMETA(DisplayName = "GOLD"),
	END
};

UENUM(BlueprintType)
enum class ERarity : uint8
{
	NORMAL = 0 UMETA(DisplayName = "NORMAL"),
	RARE UMETA(DisplayName = "RARE"),
	UNIQUE UMETA(DisplayName = "UNIQUE"),
	LEGENDARY UMETA(DisplayName = "LEGENDARY"),

	END
};

UENUM(BlueprintType)
enum class EPostProcess : uint8
{
	OUTLINE = 0 UMETA(DisplayName = "OUTLINE"),
	

	END
};
UENUM(BlueprintType)
enum class EOutline: uint8
{
	MONSTER = 0 UMETA(DisplayName = "MONSTER"),
	ITEM UMETA(DisplayName = "ITEM"),
	NPC UMETA(DisplayName = "NPC"),


	END

};

class POT3D_API UEnumHeader
{
public:

};
