// Destruction Games. 2022

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RPGHUD_Widget.generated.h"

class UCanvasPanel;

UCLASS()
class INVENTORYPROJECTV3_API URPGHUD_Widget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UCanvasPanel* HUDCanvas;
	
private:

	bool Initialize() override;

};
