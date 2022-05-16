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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget Class")
	TSubclassOf<UUserWidget> MainHud_WidgetClass;

	UPROPERTY()
	URPGHUD_Widget* MainHUD_Widget;

	virtual void BeginPlay() override;


};
