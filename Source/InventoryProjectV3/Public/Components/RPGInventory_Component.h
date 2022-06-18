// Destruction Games. 2022

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Widgets/Layout/Anchors.h"
#include "Items/RPGInventoryConfig.h"
#include "RPGInventory_Component.generated.h"

class URPGInventory_Window_Widget;
class ARPGItem_Base;

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class INVENTORYPROJECTV3_API URPGInventory_Component : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URPGInventory_Component();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inventory")
	FName Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inventory")
	int32 SlotsNumber;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inventory")
	int32 Gold;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inventory")
	TArray<FInventorySlot> Inventory;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inventory")
	URPGInventory_Window_Widget* Inventory_Window_Widget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inventory")
	FAnchors Anchors;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inventory")
	FVector2D Alignment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WidgetClassTypes")
	TSubclassOf<URPGInventory_Window_Widget> Inventory_Window_WidgetClass;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Inventory|Functions")
	void PrepareInventory();

	UFUNCTION(BlueprintCallable, Category = "Inventory|Functions")
	void ToggleInventory();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
