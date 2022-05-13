// Destruction Games. 2022

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RPGInteract_Interface.generated.h"

UINTERFACE(Blueprintable)
class URPGInteract_Interface : public UInterface
{
	GENERATED_BODY()
};

class INVENTORYPROJECTV3_API IRPGInteract_Interface
{
	GENERATED_BODY()

	
public:

	// Interact with an object
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
	void Interact(AActor* Interactor);

	// Return name of an object
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
	FText GetName();

// 	UFUNCTION()
// 	virtual void InteractPure() = 0;
};
