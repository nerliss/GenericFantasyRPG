// Destruction Games. 2022

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RPGHealth_Component.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INVENTORYPROJECTV3_API URPGHealth_Component : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URPGHealth_Component();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HP")
	bool bDied;

	float GetCurrentHP();

	float GetMaxHP();
	
protected:

	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HP")
	float HP_Max;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HP")
	float HP_Current;

public:	

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
