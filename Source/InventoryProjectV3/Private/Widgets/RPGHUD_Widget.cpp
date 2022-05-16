// Destruction Games. 2022


#include "Widgets/RPGHUD_Widget.h"

void URPGHUD_Widget::NativeConstruct()
{
	Super::NativeConstruct();
}

bool URPGHUD_Widget::Initialize()
{
	bool Success = Super::Initialize();

	if (!Success)
	{
		return false;
	}


	return true;
}
