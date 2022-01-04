// Destruction Games. 2022

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RPGXP_Component.generated.h"

class USoundBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INVENTORYPROJECTV3_API URPGXP_Component : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URPGXP_Component();

	/** Used for XP Progress Bar in UI because PBs take values only between 0 and 1 */
	void Calculate_Percentage_XP();

	/** Used for Buffer Progress Bar in UI because PBs take values only between 0 and 1 */
	void Calculate_Percentage_Buffer();

	void Calculate_MaxXP();

	UFUNCTION(BlueprintCallable, Category = "XP|Functions")
	void AddXP(float AddedXP);

	void LevelUp();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "XP|Sounds")
	USoundBase* LevelUpSound;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "XP|Level")
	int32 Level_Current;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "XP|Level")
	int32 Level_Cap;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "XP|Experience")
	float XP_Current;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "XP|Experience")
	float XP_Current_Max;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "XP|Experience")
	float XP_Buffer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "XP|Experience")
	float CurrentPercentage_XP;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "XP|Experience")
	float CurrentPercentage_Buffer;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
