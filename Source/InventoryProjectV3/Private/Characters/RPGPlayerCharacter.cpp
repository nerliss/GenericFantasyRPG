// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/RPGPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DrawDebugHelpers.h"

// Print string on screen macro
#define DEBUGMESSAGE(x, ...) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT(x), __VA_ARGS__));}

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

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Set turn rates
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

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

}

// Called to bind functionality to input
void ARPGPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Setup action bindings
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);


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

AActor* ARPGPlayerCharacter::Linetrace_Camera(float TraceLength, bool bDrawDebugLine)
{
	FVector StartLoc = CameraComp->GetComponentLocation();
	FVector EndLoc = (StartLoc + (CameraComp->GetForwardVector() * TraceLength)); // Start location of linetrace is added to camera's forward vector which is multiplied by Trace length

	FHitResult HitResult;

	FCollisionQueryParams CQP;
	CQP.AddIgnoredActor(this);

	bool bHitResult = GetWorld()->LineTraceSingleByChannel(HitResult, StartLoc, EndLoc, ECC_WorldDynamic, CQP);

	

	if (bHitResult)
	{
		// Draw debug line if set to
		if (bDrawDebugLine)
		{
			DrawDebugLine(GetWorld(), StartLoc, EndLoc, FColor::Red, false, 4.f, 0, 2.f);
		}

		AActor* HitActor = HitResult.GetActor();

// 		if (HitActor->GetClass()->ImplementsInterface(BPI_Interact::StaticClass()))
// 		{
// 			return;
// 		}

		// TODO: DoesInplementInterface() using C++ means create the Interface in C++
		InteractActor = HitActor;

		return InteractActor;
	}


	return InteractActor = NULL;
}
