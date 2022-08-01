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
enum class ESpawnTextTypes : uint8
{
	DAMAGED_PLAYER UMETA(DisplayName = "DAMAGED_PLAYER"),
	DAMAGED_MONSTER UMETA(DisplayName = "DAMAGED_MONSTER"),
	HEAL UMETA(DisplayName = "HEAL"),

	END
};

UENUM(BlueprintType)
enum class EUnitJobs : uint8
{
	NONE  UMETA(DisplayName = "NONE"),
	PALADIN UMETA(DisplayName = "PALADIN"),
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
	START UMETA(DisplayName = "START"),
	ATTACK UMETA(DisplayName = "ATTACK"),
	DEAD UMETA(DisplayName = "DEAD"),

	END
};

UENUM(BlueprintType)
enum class EWeaponSounds : uint8
{
	PRIMARY UMETA(DisplayName = "PRIMARY"),
	SKILL UMETA(DisplayName = "SKILL"),

	END
};

UENUM(BlueprintType)
enum class ETableDatas : uint8
{
	UNIT  = 0 UMETA(DisplayName = "UNIT"), 
	MONSTER UMETA(DisplayName = "MONSTER"),
	ITEM UMETA(DisplayName = "ITEM"),
	SKILL UMETA(DisplayName = "SKILL"),


	END
};

UENUM(BlueprintType)
enum class EItemWeaponTypes : uint8
{
	NONE = 0 UMETA(DisplayName = "NONE"),
	SWORD UMETA(DisplayName = "SWORD"),
	STAFF UMETA(DisplayName = "STAFF"),
	SPEAR UMETA(DisplayName = "SPEAR"),
	BOW UMETA(DisplayName = "BOW"),

	END
};

UENUM(BlueprintType)
enum class EItemArmorTypes : uint8
{
	NONE = 0 UMETA(DisplayName = "NONE"),
	HELMET UMETA(DisplayName = "HELMET"),
	ARMOR UMETA(DisplayName = "ARMOR"),
	PANTS UMETA(DisplayName = "PANTS"),
	BOOTS UMETA(DisplayName = "BOOTS"),

	END
};
UENUM(BlueprintType)
enum class EItemConsumableTypes : uint8
{
	NONE = 0 UMETA(DisplayName = "NONE"),
	POTION UMETA(DisplayName = "HELMET"),
	BUFF UMETA(DisplayName = "BUFF"),


	END
};


UENUM(BlueprintType)
enum class EItemTypes : uint8
{
	NONE = 0 UMETA(DisplayName = "NONE"),
	WEAPON UMETA(DisplayName = "WEAPON"),
	ARMOR UMETA(DisplayName = "ARMOR"),
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
enum class EStatTypes : uint8
{
	STRENGH = 0 UMETA(DisplayName = "STRENGH"),
	DEXTERITY UMETA(DisplayName = "DEXTERITY"),
	INTELIGENCE UMETA(DisplayName = "INTELIGENCE"),
	RESILIENCE UMETA(DisplayName = "RESILIENCE"),
	LUCK UMETA(DisplayName = "LUCK"),
	HP UMETA(DisplayName = "HP_UP"),
	MP UMETA(DisplayName = "MP_UP"),
	END
};

UENUM(BlueprintType)
enum class ESkillTypes : uint8
{
	ACTIVE = 0 UMETA(DisplayName = "ACTIVE"),
	PASSIVE UMETA(DisplayName = "PASSIVE"),

	END
};

UENUM(BlueprintType)
enum class ESkillAttackTypes : uint8
{
	MELEE = 0 UMETA(DisplayName = "MELEE"),
	MAGIC UMETA(DisplayName = "MAGIC"),
	RECOVERY UMETA(DisplayName = "RECOVERY"),
	BUFF UMETA(DisplayName = "BUFF"),
	DEBUFF UMETA(DisplayName = "DEBUFF"),

	END
};
UENUM(BlueprintType)
enum class ERecoveryTypes : uint8
{
	NONE = 0 UMETA(DisplayName = "NONE"),
	HP  UMETA(DisplayName = "HP"),
	MP UMETA(DisplayName = "MP"),

	END
};
UENUM(BlueprintType)
enum class EBuffTypes : uint8
{
	NONE = 0 UMETA(DisplayName = "NONE"),
	HP  UMETA(DisplayName = "HP"),
	MP UMETA(DisplayName = "MP"),
	RESILIENCE UMETA(DisplayName = "RESILIENCE"),

	ATTACK_SPEED UMETA(DisplayName = "ATTACK_SPEED"),
	MOVE_SPEED UMETA(DisplayName = "MOVE_SPEED"),
	
	STRENGH UMETA(DisplayName = "STRENGH"),
	DEXTERITY UMETA(DisplayName = "DEXTERITY"),
	INTELIGENCE UMETA(DisplayName = "INTELIGENCE"),
	LUCK UMETA(DisplayName = "LUCK"),

	END
};

UENUM(BlueprintType)
enum class EPaladinSkillNames : uint8
{
	MELEE = 0 UMETA(DisplayName = "MELEE"),
	MAGIC UMETA(DisplayName = "MAGIC"),
	RECOVERY UMETA(DisplayName = "RECOVERY"),
	BUFF UMETA(DisplayName = "BUFF"),
	DEBUFF UMETA(DisplayName = "DEBUFF"),

	END
};
UENUM(BlueprintType)
enum class ESlotTypes : uint8
{
	NONE UMETA(DisplayName = "NONE"),
	ITEM UMETA(DisplayName = "ITEM"),
	EQUIPMENT UMETA(DisplayName = "EQUIPMENT"),
	SKILL UMETA(DisplayName = "SKILL"),

	END
};


UENUM(BlueprintType)
enum class EPostProcess : uint8
{
	OUTLINE = 0 UMETA(DisplayName = "OUTLINE"),
	DEPTH  UMETA(DisplayName = "DEPTH"),


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

UENUM(BlueprintType)
enum class ECameraShake : uint8
{
	NORMAL = 0 UMETA(DisplayName = "NORMAL"),
	STRONG UMETA(DisplayName = "STRONG"),
	EARTH_QUAKE UMETA(DisplayName = "EARTH_QUAKE"),


	END

};


class POT3D_API UEnumHeader
{
public:

};
