// Destruction Games. 2022


#include "Components/RPGHealth_Component.h"

// Sets default values for this component's properties
URPGHealth_Component::URPGHealth_Component()
{
	PrimaryComponentTick.bCanEverTick = false;

	// Set default HP amount
	HP_Max = 100.f;

	bDied = false;
	
}


// Called when the game starts
void URPGHealth_Component::BeginPlay()
{
	Super::BeginPlay();

	// Set current HP to max HP
	HP_Current = HP_Max;
}


// Called every frame
void URPGHealth_Component::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

