// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/RPGInteract_Interface.h"
#include "RPGPlayerCharacter.generated.h"

class URPGXP_Component;
class URPGHealth_Component;
class URPGReputation_Component;
class URPGInventory_Component;
class UCameraComponent;
class USpringArmComponent;
class UPointLightComponent;
class AActor;
class USoundBase;
class UAnimMontage;
class URPGHUD_Widget;

UCLASS()
class INVENTORYPROJECTV3_API ARPGPlayerCharacter : public ACharacter /*, public IRPGInteract_Interface*/ 
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARPGPlayerCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComp;

	/** Experience component stores everything about Experience, Skill Points, Skills and Talents (in future) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	URPGXP_Component* XPComp;

	/** Health component responds for actors hit points, damage behavior etc. 
	* TODO: Turn this component into Stat component that will be storing different player stats such as HP, MP, Strength, Agility etc.  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	URPGHealth_Component* HPComp;

	/** Reputation component stores all the data about factions and their possible rewards */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	URPGReputation_Component* ReputationComp;

	/** Inventory component stores data about items */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	URPGInventory_Component* InventoryComp;

	/** Flashlight (more like a test feature) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UPointLightComponent* FlashlightComp;

	/** Reference to HUD Widget - is set in RPGPlayer_Controller */
	UPROPERTY()
	URPGHUD_Widget* MainHUD_WidgetRef;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	void StartJumping();

	void StopJumping();

	/** Sprint start */
	void StartSprinting();

	/** Sprint end */
	void StopSprinting();

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	UFUNCTION(BlueprintCallable, Category = "HP|Death|Functions")
	void Death();

	/** Called in blueprints to add some cosmetic stuff that is difficult/impossible to implement in C++ to death event
	 * (i.e. timelines, widgets that are created in BP etc.)
	 */
	UFUNCTION(BlueprintImplementableEvent, Category = "HP|Death|Functions")
	void OnDied();

	/** Switch camera POV to Third Person if in First Person and vise versa */
	UFUNCTION(BlueprintCallable, Category = "Camera")
	void SwitchPOV();

	UFUNCTION(BlueprintImplementableEvent, Category = "Camera|Events")
	void OnPOVChanged();

	UFUNCTION(BlueprintCallable, Category = "Linetrace|Camera")
	AActor* Linetrace_Camera(float inTraceLength, bool bDrawDebugLine);

	void Interact();

	/** Camera boom lengths */
	float MaxTargetBoomLength;
	float MinTargetBoomLength;

	/** POV states */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Linetrace|Trace")
	bool bIsFP;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Linetrace|Trace")
	bool bIsTP;

	/** Linetrace length that changes depending on POV */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Linetrace|Trace")
	float TraceLength;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Dialog|State")
	bool bInDialog;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Linetrace|Camera|Actor")
	AActor* InteractActor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HP|Animations")
	UAnimMontage* DeathMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HP|Sounds")
	USoundBase* DeathSound;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
