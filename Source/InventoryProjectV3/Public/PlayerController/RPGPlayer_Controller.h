// Destruction Games. 2022

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RPGPlayer_Controller.generated.h"

class URPGHUD_Widget;

UCLASS()
class INVENTORYPROJECTV3_API ARPGPlayer_Controller : public APlayerController
{
	GENERATED_BODY()

	ARPGPlayer_Controller();

public:

	virtual void BeginPlay() override;

	// Blueprint reference to a Main HUD Widget
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD Widget|Class")
	TSubclassOf<UUserWidget> MainHUD_WidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HUD Widget|Reference")
	URPGHUD_Widget* MainHUD_Widget;
};
