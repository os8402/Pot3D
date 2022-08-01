#include "UI/WG_Tooltip_Gauge.h"
#include "Stat/ACP_StatInfo.h"
#include <Components/TextBlock.h>


void UWG_Tooltip_Gauge::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (_currentStatComp.IsValid())
	{
		RefreshUI();
	}


}

void UWG_Tooltip_Gauge::RefreshUI()
{

	_TB_Name->SetText(_name);
	_TB_Info->SetText(_info);

	int32 value , maxValue = 0;

	if (_statType == EStatTypes::HP)
	{
		value = _currentStatComp.Get()->GetHp();
		maxValue = _currentStatComp.Get()->GetMaxHp();
	}
	else if (_statType == EStatTypes::MP)
	{
		value = _currentStatComp.Get()->GetMp();
		maxValue = _currentStatComp.Get()->GetMaxMp();
	}

	FString str = FString::Printf(TEXT("%d/%d"), value , maxValue);

	_TB_Value->SetText(FText::FromString(str));
}
