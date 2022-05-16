// Destruction Games. 2022


#include "PlayerController/RPGPlayer_Controller.h"
#include "Blueprint/UserWidget.h"
#include "Widgets/RPGHUD_Widget.h"
#include "Characters/RPGPlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Utility/Utility.h"

ARPGPlayer_Controller::ARPGPlayer_Controller()
{
	MainHUD_Widget = nullptr;
	MainHud_WidgetClass = nullptr;
}

void ARPGPlayer_Controller::BeginPlay()
{
	Super::BeginPlay();

	if (MainHud_WidgetClass)
	{
		MainHUD_Widget = Cast<URPGHUD_Widget>(CreateWidget(GetWorld(), MainHud_WidgetClass));

		if (MainHUD_Widget)
		{
			MainHUD_Widget->AddToViewport();

			ARPGPlayerCharacter* PlayerRef = Cast<ARPGPlayerCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));

			PlayerRef->MainHUD_WidgetRef = MainHUD_Widget;
			DEBUGMESSAGE(3.f, "MainHUD references set");
		}
	}

}
