// Destruction Games. 2022


#include "Components/RPGInventory_Component.h"
#include "PlayerController/RPGPlayer_Controller.h"
#include "Items/RPGItem_Base.h"
#include "Widgets/Inventory/RPGInventory_Window_Widget.h"
#include "Widgets/RPGHUD_Widget.h"
#include "Utility/Utility.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"

// Sets default values for this component's properties
URPGInventory_Component::URPGInventory_Component()
{
	PrimaryComponentTick.bCanEverTick = false;

	Name = "";
	SlotsNumber = 0;
	Anchors = 0.5f;
	Alignment = FVector2D(1.0f, 0.5f);
}

// Called when the game starts
void URPGInventory_Component::BeginPlay()
{
	Super::BeginPlay();

	PrepareInventory();
}

// Called every frame
void URPGInventory_Component::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void URPGInventory_Component::PrepareInventory()
{
	Inventory.SetNum(SlotsNumber);

	for (int i = 0; i < Inventory.Num(); i++)
	{
		FInventorySlot Slot = Inventory[i];
		TSubclassOf<ARPGItem_Base> ItemClass = Slot.Item.Class;
		int32 Quantity = Slot.Quantity;

		if (ItemClass)
		{
			// Get a reference to a default object of a Base Item class
// 			ARPGItem_Base* DefaultActor = Cast<ARPGItem_Base>(ARPGItem_Base::StaticClass()->GetDefaultObject(true));
// 			Slot.Item = DefaultActor->Item;

			ARPGItem_Base* DefaultObject = ItemClass.GetDefaultObject();
			Slot.Item = DefaultObject->Item;

			//Slot.Item = Slot.Item; // Works for runtime-created items in inventory. For design time-created should use GetDefaultObject() somehow
			Slot.Quantity = Quantity;
		}
	}
}

void URPGInventory_Component::ToggleInventory()
{
	ARPGPlayer_Controller* PC = Cast<ARPGPlayer_Controller>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (Inventory_Window_Widget)
	{
		Inventory_Window_Widget->RemoveFromParent();
		Inventory_Window_Widget = nullptr;
		
		PC->bShowMouseCursor = false;
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(PC);
	}
	else
	{
		PrepareInventory();

		if (Inventory_Window_WidgetClass)
		{
			Inventory_Window_Widget = Cast<URPGInventory_Window_Widget>(CreateWidget(GetWorld(), Inventory_Window_WidgetClass));

			DEBUGMESSAGE(5.f, FColor::Green, "Inventory class widget set");

			if (Inventory_Window_Widget)
			{
				PC->MainHUD_Widget->HUDCanvas->AddChildToCanvas(Inventory_Window_Widget);

				// This will probably get us the most recently-created slot (last slot)
				int32 LastSlot = PC->MainHUD_Widget->HUDCanvas->GetChildrenCount() - 1;

				UCanvasPanelSlot* InventoryWindowSlot = CastChecked<UCanvasPanelSlot>(PC->MainHUD_Widget->HUDCanvas->GetSlots()[LastSlot]);

				// Setup inventory window slot
				InventoryWindowSlot->bAutoSize = true;
				InventoryWindowSlot->SetAlignment(Alignment);
				InventoryWindowSlot->SetAnchors(Anchors);

				// Set input mode
				UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(PC);
				PC->bShowMouseCursor = true;

				DEBUGMESSAGE(5.f, FColor::Green, "Inventory initialized");
			}
			else
			{
				DEBUGMESSAGE(5.f, FColor::Red, "Inventory was not created");
			}
		}
		else
		{
			DEBUGMESSAGE(5.f, FColor::Red, "Inventory class not set");
		}
	}
}
