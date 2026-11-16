
#include "CombatWeapon.h"
#include "CombatHealthComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
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

    // Find the muzzle point attached to the player's hand
    // Find the specific arrow component named MuzzlePoint
    UArrowComponent* MuzzlePoint = nullptr;

    TArray<UArrowComponent*> ArrowComponents;
    OwnerPawn->GetComponents<UArrowComponent>(ArrowComponents);

    for (UArrowComponent* Arrow : ArrowComponents)
    {
        if (Arrow && Arrow->GetFName() == FName(TEXT("MuzzlePoint")))
        {
            MuzzlePoint = Arrow;
            break;
        }
    }

    // Use the muzzle location if available
    FVector TraceStart = MuzzlePoint
        ? MuzzlePoint->GetComponentLocation()
        : CameraLocation;

    // Set up hit detection
    FHitResult HitResult;

    FCollisionQueryParams TraceParams;
    TraceParams.AddIgnoredActor(OwnerPawn);
    TraceParams.AddIgnoredActor(this);

    // Find the direction from the muzzle toward the camera's aim point
    FVector ShotDirection =
        (TraceEnd - TraceStart).GetSafeNormal();

    // Calculate the shot endpoint from the muzzle
    FVector MuzzleTraceEnd =
        TraceStart + (ShotDirection * AttackRange);

    // Perform the line trace from the muzzle
    bool bHit = World->LineTraceSingleByChannel(
        HitResult,
        TraceStart,
        MuzzleTraceEnd,
        ECC_Visibility,
        TraceParams
    );

    // Draw a debug line from the muzzle
    DrawDebugLine(
        World,
        TraceStart,
        bHit ? HitResult.ImpactPoint : MuzzleTraceEnd,
        bHit ? FColor::Green : FColor::Red,
        false,
        1.0f,
        0,
        2.0f
    );


    if (bHit)
    {
        AActor* HitActor = HitResult.GetActor();

        UE_LOG(
            LogTemp,
            Warning,
            TEXT("Weapon hit: %s"),
            *GetNameSafe(HitActor)
        );

        // Check whether the hit actor has a Health Component
        if (HitActor)
        {
            UCombatHealthComponent* HealthComponent =
                HitActor->FindComponentByClass<UCombatHealthComponent>();

            if (HealthComponent)
            {
                // Apply damage to the target
                HealthComponent->TakeDamage(AttackDamage);

                UE_LOG(
                    LogTemp,
                    Warning,
                    TEXT("Applied %.1f damage to %s"),
                    AttackDamage,
                    *GetNameSafe(HitActor)
                );
            }
            else
            {
                UE_LOG(
                    LogTemp,
                    Warning,
                    TEXT("Hit actor has no Health Component!")
                );
            }
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Weapon missed!"));
    }

}


