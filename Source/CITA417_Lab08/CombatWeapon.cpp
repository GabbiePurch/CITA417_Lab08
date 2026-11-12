
#include "CombatWeapon.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"
#include "DrawDebugHelpers.h"

// Sets default values
ACombatWeapon::ACombatWeapon()
{
    // Weapon does not need to update every frame
    PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts
void ACombatWeapon::BeginPlay()
{
    Super::BeginPlay();
}


void ACombatWeapon::Fire()
{
    // Make sure the weapon has a valid owner
    APawn* OwnerPawn = Cast<APawn>(GetOwner());

    if (!OwnerPawn)
    {
        UE_LOG(LogTemp, Warning, TEXT("Weapon has no valid Pawn owner!"));
        return;
    }

    // Get the player's controller
    APlayerController* PlayerController =
        Cast<APlayerController>(OwnerPawn->GetController());

    if (!PlayerController)
    {
        UE_LOG(LogTemp, Warning, TEXT("Weapon has no valid PlayerController!"));
        return;
    }

    // Make sure the world is valid
    UWorld* World = GetWorld();

    if (!World)
    {
        UE_LOG(LogTemp, Warning, TEXT("Weapon has no valid world!"));
        return;
    }

    // Check the attack cooldown
    const float CurrentTime = World->GetTimeSeconds();

    if (CurrentTime - LastFireTime < AttackCooldown)
    {
        return;
    }

    LastFireTime = CurrentTime;

    // Get the player's camera position and direction
    FVector CameraLocation;
    FRotator CameraRotation;

    PlayerController->GetPlayerViewPoint(
        CameraLocation,
        CameraRotation
    );

    // Calculate where the trace should end
    FVector TraceEnd =
        CameraLocation +
        (CameraRotation.Vector() * AttackRange);

    // Set up hit detection
    FHitResult HitResult;

    FCollisionQueryParams TraceParams;
    TraceParams.AddIgnoredActor(OwnerPawn);
    TraceParams.AddIgnoredActor(this);

    // Perform the line trace
    bool bHit = World->LineTraceSingleByChannel(
        HitResult,
        CameraLocation,
        TraceEnd,
        ECC_Visibility,
        TraceParams
    );

    // Draw a debug line to visualize the shot
    DrawDebugLine(
        World,
        CameraLocation,
        bHit ? HitResult.ImpactPoint : TraceEnd,
        bHit ? FColor::Green : FColor::Red,
        false,
        1.0f,
        0,
        2.0f
    );

    // Display hit or miss information
    if (bHit)
    {
        UE_LOG(
            LogTemp,
            Warning,
            TEXT("Weapon hit: %s"),
            *GetNameSafe(HitResult.GetActor())
        );
    }
    else
    {
        UE_LOG(
            LogTemp,
            Warning,
            TEXT("Weapon missed!")
        );
    }
}


