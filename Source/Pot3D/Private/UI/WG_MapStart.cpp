#include "UI/WG_MapStart.h"
#include <Components/TextBlock.h>

void UWG_MapStart::UpdateText(FText text)
{
	_TB_MapName->SetText(text);
	PlayAnimation(_WA_Fade);
}
