// Destruction Games. 2022


#include "Items/RPGItem_Base.h"

// Sets default values
ARPGItem_Base::ARPGItem_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARPGItem_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARPGItem_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

