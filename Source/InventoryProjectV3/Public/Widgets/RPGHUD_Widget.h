// Destruction Games. 2022

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RPGHUD_Widget.generated.h"

class UCanvasPanel;
class URPGInteractionPrompt_Widget;
class URPGXPBar_Widget;

UCLASS()
class INVENTORYPROJECTV3_API URPGHUD_Widget : public UUserWidget
{
	GENERATED_BODY()
	
private:

	bool Initialize() override;

public:

	virtual void NativeConstruct() override;

	// Canvas is used to store different user-created widgets
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UCanvasPanel* HUDCanvas;

	// TODO: Doesn't work the way normal widgets would. Figure it out
// 	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
// 	URPGXPBar_Widget* XPBar_Widget;

	// In BP set to BP child of RPGInteractionPrompt_Widget
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class Types")
	TSubclassOf<UUserWidget> InteractionPrompt_WidgetClass;

	// Widget reference
	UPROPERTY()
	URPGInteractionPrompt_Widget* InteractionPrompt_Widget;

	/** 
	* bShowMessage = true creates an InteractionPrompt_Widget,
	* bShowMessage = false destroys the widget and nullifies it reference
	* Use bShowMessage = false if you want to destroy already existing message
	*/
	UFUNCTION(BlueprintCallable, Category = "Widget")
	void DisplayInteractionMessage(bool bShowMessage, FText TargetName);
	
};
