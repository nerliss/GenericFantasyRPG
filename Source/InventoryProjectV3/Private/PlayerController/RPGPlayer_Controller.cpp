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
	MainHUD_WidgetClass = nullptr;
}

void ARPGPlayer_Controller::BeginPlay()
{
	Super::BeginPlay();

	// Check if MainHUD_WidgetClass is set (in blueprints)
	if (MainHUD_WidgetClass)
	{
		// Create widget derived from URPGHUD_Widget
		MainHUD_Widget = Cast<URPGHUD_Widget>(CreateWidget(GetWorld(), MainHUD_WidgetClass));

		if (MainHUD_Widget)
		{
			// Set player reference
			ARPGPlayerCharacter* PlayerRef = Cast<ARPGPlayerCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));

			// Set HUD widget reference in Player character
			if (PlayerRef)
			{
				PlayerRef->MainHUD_WidgetRef = MainHUD_Widget;

				MainHUD_Widget->AddToViewport();
				DEBUGMESSAGE(3.f, FColor::Green, "MainHUD references set");
			}

		}
	}

}
