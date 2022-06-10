#include "UI/WG_Tooltip.h"
#include "UI/WG_Inventory_ItemSlot.h"
#include "UI/WG_TitleBar.h"
#include "UI/WG_BonusStat.h"

#include "Item/OBJ_Item.h"
#include "Item/OBJ_Weapon_Item.h"
#include "Item/OBJ_Armor_Item.h"
#include "Item/OBJ_Consumable_Item.h"

#include <Blueprint/WidgetTree.h>
#include <Components/Image.h>
#include <COmponents/TextBlock.h>
#include <COmponents/VerticalBox.h>


void UWG_Tooltip::RefreshUI(UOBJ_Item* item)
{
	_WBP_TitleBar->SetTitle(item->GetItemName());
	_WBP_Inventory_ItemSlot->SetItem(item);

	//TODO : Bonus Stat Widget
	UVerticalBox* verticalBox = WidgetTree->FindWidget<UVerticalBox>("_VB_BonusStatList");

	//TODO : Bonus Stat All Clear
	verticalBox->ClearChildren();

	if (verticalBox && item)
	{

		for (auto& bonus : item->GetBonusStats())
		{
			UWG_BonusStat* bonusStat = CreateWidget<UWG_BonusStat>(this, _bonusStatClass);
			verticalBox->AddChild(bonusStat);
			
			const UEnum* stateEnum = FindObject<UEnum>(ANY_PACKAGE, TEXT("EStatTypes") , true);
			
			FString statName = stateEnum->GetNameStringByValue((int32)bonus.Key);
			
			FString bonusStr = LocalizationUI::ConvertToUIText(statName);
			FString conv = FString::Printf(TEXT("+%d %s 증가"), bonus.Value, *bonusStr);
			
			bonusStat->SetBonusStatText(FText::FromString(conv), _gradeColors[(int32)item->GetRarity()]);

		}

	}

	Localization(item);


}

void UWG_Tooltip::Localization(UOBJ_Item* item)
{
	//TODO : 문서로 불러와야 하지만.. 나중에..

	int32 itemId = item->GetItemId();
	ERarity rarity = item->GetRarity();
	EItemTypes itemType = item->GetItemType();


	_WBP_TitleBar->SetGradeTexture(_gradeTextures[(int32)rarity]);

	FString strRarity; 
	FString strItemType;

	switch (rarity)
	{
	case ERarity::NORMAL:
		strRarity = FString(TEXT("일반"));
		break;
	case ERarity::RARE:
		strRarity = FString(TEXT("레어"));
		break;
	case ERarity::UNIQUE:
		strRarity = FString(TEXT("영웅"));
		break;
	case ERarity::LEGENDARY:
		strRarity = FString(TEXT("전설"));
		break;

	default:
		break;
	}

	UOBJ_Weapon_Item* weaponItem = Cast<UOBJ_Weapon_Item>(item);
	UOBJ_Armor_Item* armorItem = Cast<UOBJ_Armor_Item>(item);
	UOBJ_Consumable_Item* consumableItem = Cast<UOBJ_Consumable_Item>(item);

	if (weaponItem)
	{
		EItemWeaponTypes weaponType = weaponItem->GetWeaponType();
		
		switch (weaponType)
		{
		case EItemWeaponTypes::SWORD:
			_TB_ItemMoreInfo->SetText(UtilsLib::ConvertToFText(TEXT("검")));
			break;
		case EItemWeaponTypes::STAFF:
			_TB_ItemMoreInfo->SetText(UtilsLib::ConvertToFText("지팡이"));
			break;
		case EItemWeaponTypes::SPEAR:
			_TB_ItemMoreInfo->SetText(UtilsLib::ConvertToFText("창"));
			break;
		case EItemWeaponTypes::BOW:
			_TB_ItemMoreInfo->SetText(UtilsLib::ConvertToFText("활"));
			break;

		default:
			break;
		}
		
		int32 minAtk = weaponItem->GetStatData()._minAtk;
		int32 maxAtk = weaponItem->GetStatData()._maxAtk;

		FText atkText = UtilsLib::ConvertToFText(minAtk , maxAtk);

		_TB_Amount->SetText(atkText);
		_TB_AmountInfo->SetText(UtilsLib::ConvertToFText(TEXT("무기 공격력")));

	}
	else if (armorItem)
	{
		EItemArmorTypes armorType = armorItem->GetArmorType();

		switch (armorType)
		{

		case EItemArmorTypes::HELMET:
			_TB_ItemMoreInfo->SetText(UtilsLib::ConvertToFText(TEXT("모자")));
			break;
		case EItemArmorTypes::ARMOR:
			_TB_ItemMoreInfo->SetText(UtilsLib::ConvertToFText(TEXT("갑옷")));
			break;
		case EItemArmorTypes::PANTS:
			_TB_ItemMoreInfo->SetText(UtilsLib::ConvertToFText(TEXT("바지")));
			break;
		case EItemArmorTypes::BOOTS:
			_TB_ItemMoreInfo->SetText(UtilsLib::ConvertToFText(TEXT("신발")));
			break;

		default:
			break;
		}

		_TB_Amount->SetText(UtilsLib::ConvertToFText(armorItem->GetStatData()._defence));
		_TB_AmountInfo->SetText(UtilsLib::ConvertToFText(TEXT("방어도")));
	}
	else if (consumableItem)
	{
		
	}


	switch (itemType)
	{

	case EItemTypes::WEAPON :
		strItemType = FString(TEXT("무기"));

		break;
	case EItemTypes::ARMOR:
		strItemType = FString(TEXT("방어구"));
		break;
	case EItemTypes::CONSUMABLE:
		strItemType = FString(TEXT("소모품"));
		break;
	case EItemTypes::JEWEL:
		strItemType = FString(TEXT("보석"));
		break;
	case EItemTypes::GOLD:
		strItemType = FString(TEXT("금화"));
		break;

	default:
		break;
	}


	_TB_Grade->SetText(FText::FromString(strRarity));
	_TB_Grade->SetColorAndOpacity(_gradeColors[(int32)rarity]);

	_TB_ItemType->SetText(FText::FromString(strItemType));

	

}


