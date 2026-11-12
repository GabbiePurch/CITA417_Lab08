// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CombatWeapon.generated.h"


UCLASS()
class CITA417_LAB08_API ACombatWeapon : public AActor
{
    GENERATED_BODY()

public:
    ACombatWeapon();

    // Called when the player fires the weapon
    UFUNCTION(BlueprintCallable, Category = "Combat")
    void Fire();

protected:
    virtual void BeginPlay() override;

    // Maximum distance the weapon can hit
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    float AttackRange = 2000.0f;

    // Damage dealt per successful hit
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    float AttackDamage = 25.0f;

    // Minimum time between attacks
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    float AttackCooldown = 0.3f;

private:
    // Tracks when the weapon can fire again
    float LastFireTime = -1000.0f;
};

