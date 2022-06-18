// Destruction Games. 2022


#include "Components/RPGInventory_Component.h"
#include "Items/RPGItem_Base.h"

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
			/*ItemClass = Cast<ARPGItem_Base>(ItemClass);*/
			//Slot.Item = ItemClass.GetDefaultObject();
			//Slot.Item = Cast<FInventoryItem>(Slot.Item.Class->GetDefaultObject());
			Slot.Item = Slot.Item; // Works for runtime-created items in inventory. For design time-created should use GetDefaultObject() somehow
			Slot.Quantity = Quantity;
		}
	}
}

void URPGInventory_Component::ToggleInventory()
{
	return;
}
