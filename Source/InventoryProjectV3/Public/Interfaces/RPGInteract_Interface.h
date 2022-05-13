// Destruction Games. 2022

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RPGInteract_Interface.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable)
class URPGInteract_Interface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class INVENTORYPROJECTV3_API IRPGInteract_Interface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, Category = "Interaction")
	void Interact(AActor* Interactor);

	UFUNCTION(BlueprintNativeEvent, Category = "Interaction")
	FText GetName();

// 	UFUNCTION()
// 	virtual void InteractPure() = 0;
};
