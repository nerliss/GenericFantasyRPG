// Destruction Games. 2022

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "Engine/EngineTypes.h"
#include "RPGInventoryConfig.generated.h"

class ARPGItem_Base;

USTRUCT(Blueprintable, BlueprintType)
struct FInventoryItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory item struct")
	FName Name = "PH_Name";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory item struct")
	FName Description = "PH_Description";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory item struct")
	bool bQuestItem = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory item struct")
	bool bStackable = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory item struct")
	bool bConsumable = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory item struct")
	UTexture2D* Thumbnail = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory item struct")
	int32 MaxStackSize = 20;

	/** !!!UNUSED!!! */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory item struct")
	float Durability = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory item struct")
	TSubclassOf<ARPGItem_Base> Class = nullptr;
};

USTRUCT(Blueprintable, BlueprintType)
struct FInventorySlot
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory slot struct")
	FInventoryItem Item;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory slot struct")
	int32 Quantity;
};
