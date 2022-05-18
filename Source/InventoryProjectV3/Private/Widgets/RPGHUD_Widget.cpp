// Destruction Games. 2022


#include "Widgets/RPGHUD_Widget.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Widgets/RPGInteractionPrompt_Widget.h"
#include "Utility/Utility.h"

void URPGHUD_Widget::NativeConstruct()
{
	Super::NativeConstruct();
}

void URPGHUD_Widget::DisplayInteractionMessage(bool bShowMessage, FText TargetName)
{
	// If class is set in BP
	if (InteractionPrompt_WidgetClass)
	{
		// Show message
		if (bShowMessage)
		{
			if (!InteractionPrompt_Widget)
			{
				InteractionPrompt_Widget = Cast<URPGInteractionPrompt_Widget>(CreateWidget(GetWorld(), InteractionPrompt_WidgetClass));

				InteractionPrompt_Widget->Text_Target_Name = TargetName;

				// Configure the canvas panel slot for interaction message
				if (HUDCanvas)
				{
					HUDCanvas->AddChildToCanvas(InteractionPrompt_Widget);

					UCanvasPanelSlot* CanvasPanelSlot = CastChecked<UCanvasPanelSlot>(HUDCanvas->GetSlots()[0]);

					// Approximately lower center of the screen
					CanvasPanelSlot->SetAutoSize(true);
					CanvasPanelSlot->SetAnchors(FAnchors(0.5f, 0.5f, 0.5f, 0.5f));
					CanvasPanelSlot->SetAlignment(FVector2D(0.5f, -1.f));
					CanvasPanelSlot->SetPosition(FVector2D(0.f, 0.f));

					DEBUGMESSAGE(5.f, "Interaction prompt set and configured in the Canvas");
				}
			}
		}
		// Delete message
		else
		{
			if (InteractionPrompt_Widget)
			{
				InteractionPrompt_Widget->RemoveFromParent();
				InteractionPrompt_Widget = nullptr;
				DEBUGMESSAGE(5.f, "InteractionPrompt_Widget is DELETED in MainWidget");
			}
		}
	}
}

bool URPGHUD_Widget::Initialize()
{
	bool Success = Super::Initialize();

	if (!Success)
	{
		return false;
	}

	// TODO: Create references to multiple user-created widgets that still need to be implemented via C++

	return true;
}
