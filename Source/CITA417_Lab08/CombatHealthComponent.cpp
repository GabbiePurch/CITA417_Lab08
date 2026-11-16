// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatHealthComponent.h"

// Sets default values for this component's properties
UCombatHealthComponent::UCombatHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UCombatHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// Initialize health
	MaxHealth = FMath::Max(0.0f, MaxHealth);
	CurrentHealth = MaxHealth;
	bIsDead = (CurrentHealth <= 0.0f);

	UE_LOG(LogTemp, Warning,
		TEXT("%s initialized with %.1f health"),
		*GetNameSafe(GetOwner()),
		CurrentHealth);
	
}


// Apply damage to the target
void UCombatHealthComponent::TakeDamage(float DamageAmount)
{
    // Ignore damage if already dead or damage is invalid
    if (bIsDead || DamageAmount <= 0.0f)
    {
        return;
    }

    // Reduce health without going below zero
    CurrentHealth = FMath::Clamp(
        CurrentHealth - DamageAmount,
        0.0f,
        MaxHealth
    );

    UE_LOG(LogTemp, Warning,
        TEXT("%s took %.1f damage! Health remaining: %.1f"),
        *GetNameSafe(GetOwner()),
        DamageAmount,
        CurrentHealth);

    // Check for death
    if (CurrentHealth <= 0.0f)
    {
        bIsDead = true;

        UE_LOG(LogTemp, Warning,
            TEXT("%s has died!"),
            *GetNameSafe(GetOwner()));

        // Notify Blueprints that the target died
        OnDeath.Broadcast();
    }
}
