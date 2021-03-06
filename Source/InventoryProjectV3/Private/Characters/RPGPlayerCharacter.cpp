// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/RPGPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/RPGXP_Component.h"
#include "Components/RPGHealth_Component.h"
#include "Components/RPGReputation_Component.h"
#include "Components/RPGInventory_Component.h"
#include "Components/PointLightComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Widgets/RPGInteractionPrompt_Widget.h"
#include "Widgets/RPGHUD_Widget.h"
#include "Blueprint/UserWidget.h"
#include "Utility/Utility.h"

// Sets default values
ARPGPlayerCharacter::ARPGPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set initial capsule size
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

	// Character movement configuration
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f; // default is 600
	GetCharacterMovement()->AirControl = 0.2f; // default is 0.2

	// SpringArm (Camera boom) component configuration
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(GetCapsuleComponent(), "head");
	SpringArmComp->TargetArmLength = 500.f;
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SocketOffset = FVector(0.f, 80.f, 0.f); // Give camera more Skyrim-like style

	// Camera component configuration
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);
	CameraComp->bUsePawnControlRotation = false;

	// Flashlight component
	FlashlightComp = CreateDefaultSubobject<UPointLightComponent>(TEXT("FlashlightComp"));
	FlashlightComp->SetSourceRadius(170.f);

	// Give it more yellow-ish color
	FlashlightComp->SetUseTemperature(true);
	FlashlightComp->SetTemperature(4680.f);
	FlashlightComp->SetCastShadows(false);
	FlashlightComp->SetLightColor(FLinearColor(1.f, 0.78f, 0.13f, 1));

	// Create XP component
	XPComp = CreateDefaultSubobject<URPGXP_Component>(TEXT("XPComp"));

	// Create HP component
	HPComp = CreateDefaultSubobject<URPGHealth_Component>(TEXT("HPComp"));

	// Create Reputation component
	ReputationComp = CreateDefaultSubobject<URPGReputation_Component>(TEXT("ReputationComp"));

	// Create inventory component
	InventoryComp = CreateDefaultSubobject<URPGInventory_Component>(TEXT("InventoryComp"));

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Set turn rates
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Camera
	MaxTargetBoomLength = SpringArmComp->TargetArmLength;
	MinTargetBoomLength = 0.f;

	// POV
	bIsTP = true;
	bIsFP = false;

	// Dialog
	bInDialog = false;
}

// Called when the game starts or when spawned
void ARPGPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// SpringArm offset 
	SpringArmComp->SetRelativeLocation(FVector(0.f, 0.f, 65.f));
}

// Called every frame
void ARPGPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Linetrace_Camera(TraceLength, false);
}

// Called to bind functionality to input
void ARPGPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Setup action bindings
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ARPGPlayerCharacter::StartJumping);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ARPGPlayerCharacter::StopJumping);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ARPGPlayerCharacter::StartSprinting);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ARPGPlayerCharacter::StopSprinting);
	PlayerInputComponent->BindAction("SwitchPOV", IE_Pressed, this, &ARPGPlayerCharacter::SwitchPOV);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ARPGPlayerCharacter::Interact);

	// Setup axis bindings
	PlayerInputComponent->BindAxis("MoveForward", this, &ARPGPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ARPGPlayerCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ARPGPlayerCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ARPGPlayerCharacter::LookUpAtRate);
}

void ARPGPlayerCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.f))
	{
		// Define rotation to get forward vector from
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// Get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ARPGPlayerCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// Find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// Get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void ARPGPlayerCharacter::StartJumping()
{
	ACharacter::Jump();

	// TODO: Make character stop rotating while in air
}

void ARPGPlayerCharacter::StopJumping()
{
	ACharacter::StopJumping();
}

void ARPGPlayerCharacter::StartSprinting()
{
	GetCharacterMovement()->MaxWalkSpeed = 4500.f;
}

void ARPGPlayerCharacter::StopSprinting()
{
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
}

void ARPGPlayerCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ARPGPlayerCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ARPGPlayerCharacter::Death()
{
	if (HPComp && !HPComp->bDied)
	{
		HPComp->bDied = true;

		// Disable collision
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		
		// Disable input
		DisableInput(UGameplayStatics::GetPlayerController(this, 0));

		// Call blueprint event
		OnDied();

		/* Cosmetics */
		// AnimMontage
		if (DeathMontage)
		{
			PlayAnimMontage(DeathMontage);
		}

		// SFX
		if (DeathSound)
		{
			UGameplayStatics::SpawnSound2D(this, DeathSound);
		}
	}
}

void ARPGPlayerCharacter::SwitchPOV()
{
	if (bIsTP) // to FirstPerson
	{
		SpringArmComp->TargetArmLength = MinTargetBoomLength;
		SpringArmComp->SocketOffset = FVector(0.f, 0.f, 0.f);

		GetMesh()->SetVisibility(false);

		TraceLength = 350.f;

		bIsFP = true;
		bIsTP = false;

		OnPOVChanged();
	}
	else if (bIsFP) // to ThirdPerson
	{
		SpringArmComp->TargetArmLength = MaxTargetBoomLength;
		SpringArmComp->SocketOffset = FVector(0.f, 80.f, 0.f);

		GetMesh()->SetVisibility(true);

		TraceLength = 700.f;

		bIsFP = false;
		bIsTP = true;

		OnPOVChanged();
	}
}

AActor* ARPGPlayerCharacter::Linetrace_Camera(float inTraceLength, bool bDrawDebugLine)
{
	FVector StartLoc = CameraComp->GetComponentLocation();
	FVector EndLoc = (StartLoc + (CameraComp->GetForwardVector() * inTraceLength)); // Start location of linetrace is added to camera's forward vector which is multiplied by Trace length

	FHitResult HitResult;

	FCollisionQueryParams CQP;
	CQP.AddIgnoredActor(this);

	bool bHitResult = GetWorld()->LineTraceSingleByChannel(HitResult, StartLoc, EndLoc, ECC_WorldDynamic, CQP);

	if (bHitResult && !bInDialog)
	{
		// Draw debug line if set to
		if (bDrawDebugLine)
		{
			DrawDebugLine(GetWorld(), StartLoc, EndLoc, FColor::Red, false, 4.f, 0, 2.f);
		}

		AActor* HitActor = HitResult.GetActor();

		// Show interaction prompt if actor is eligible
		if (HitActor->GetClass()->ImplementsInterface(URPGInteract_Interface::StaticClass()))
		{
			if (MainHUD_WidgetRef)
			{
				MainHUD_WidgetRef->DisplayInteractionMessage(true, IRPGInteract_Interface::Execute_GetName(HitActor));
			}
 		}
		// Delete interaction prompt if HitActior doesn't implement the interface (providing it exists)
		else
		{
			if (MainHUD_WidgetRef)
			{
				MainHUD_WidgetRef->DisplayInteractionMessage(false, FText::FromString(""));
			}
		}

		return InteractActor = HitActor;
	}

	// Delete interaction prompt if no HitActor present
	if (MainHUD_WidgetRef)
	{
		MainHUD_WidgetRef->DisplayInteractionMessage(false, FText::FromString(""));
	}

	return InteractActor = nullptr;
}

void ARPGPlayerCharacter::Interact()
{
	// Interact with object if it exists and has our Interact_Interface
	if (InteractActor && InteractActor->GetClass()->ImplementsInterface(URPGInteract_Interface::StaticClass()))
	{
		IRPGInteract_Interface::Execute_Interact(InteractActor, this);
	}
}
