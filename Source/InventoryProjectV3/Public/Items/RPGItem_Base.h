// Destruction Games. 2022

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Items/RPGInventoryConfig.h"
#include "RPGItem_Base.generated.h"

UCLASS()
class INVENTORYPROJECTV3_API ARPGItem_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARPGItem_Base();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inventory")
	FInventoryItem Item;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
