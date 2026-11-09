// Copyright Epic Games, Inc. All Rights Reserved.

#include "CITA417_Lab08Character.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Kismet/KismetMathLibrary.h"
#include "CITA417_Lab08.h"

ACITA417_Lab08Character::ACITA417_Lab08Character()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)


	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
}

void ACITA417_Lab08Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACITA417_Lab08Character::Move);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &ACITA417_Lab08Character::Look);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACITA417_Lab08Character::Look);


		// Sprinting
		EnhancedInputComponent->BindAction(SprintAction,ETriggerEvent::Started,this,&ACITA417_Lab08Character::StartSprint);

		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed,this,&ACITA417_Lab08Character::StopSprint);

	}


	else
	{
		UE_LOG(LogCITA417_Lab08, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}

}

void ACITA417_Lab08Character::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	// route the input
	DoMove(MovementVector.X, MovementVector.Y);
}

void ACITA417_Lab08Character::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// route the input
	DoLook(LookAxisVector.X, LookAxisVector.Y);
}

void ACITA417_Lab08Character::DoMove(float Right, float Forward)
{
	if (GetController() != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, Forward);
		AddMovementInput(RightDirection, Right);
	}
}

void ACITA417_Lab08Character::DoLook(float Yaw, float Pitch)
{
	if (GetController() != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void ACITA417_Lab08Character::DoJumpStart()
{
	// signal the character to jump
	Jump();
}

void ACITA417_Lab08Character::DoJumpEnd()
{
	// signal the character to stop jumping
	StopJumping();
}


void ACITA417_Lab08Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateAnimationState();
}



void ACITA417_Lab08Character::UpdateAnimationState()
{
	// Get the character's current velocity
	FVector Velocity = GetVelocity();

	// Ignore vertical movement when calculating speed
	Velocity.Z = 0.0f;

	// Calculate horizontal movement speed
	MovementSpeed = Velocity.Size();

	// Calculate movement direction relative to facing

	const FVector LocalVelocity =
		GetActorRotation().UnrotateVector(Velocity);

	MovementDirection = FMath::RadiansToDegrees(
		FMath::Atan2(LocalVelocity.Y, LocalVelocity.X)

	);

	// Check whether the character is jumping or falling
	bIsAirborne = GetCharacterMovement()->IsFalling();

}



void ACITA417_Lab08Character::StartSprint()
{
	bIsSprinting = true;

	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;

	UE_LOG(LogTemp, Warning, TEXT("Sprint Started! Speed: %.1f"), SprintSpeed);
}

void ACITA417_Lab08Character::StopSprint()
{
	bIsSprinting = false;

	GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;

	UE_LOG(LogTemp, Warning, TEXT("Sprint Stopped! Speed: %.1f"), NormalSpeed);
}
