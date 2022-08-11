#include "UI/WG_Select.h"
#include "UI/WG_Button.h"
#include "Kismet/GameplayStatics.h"
#include <Components/Button.h>

void UWG_Select::NativeConstruct()
{
	
	UButton* startBtn = _BTN_GameStart->GetSlotBtn();
	startBtn->OnClicked.AddDynamic(this,  &UWG_Select::StartGame);

}

void UWG_Select::StartGame()
{
	//TODO : ���̺� ������ ���� �� �̸� �ҷ�����  ����

	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Village"));
}
