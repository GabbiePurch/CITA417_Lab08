
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatHealthComponent.generated.h"

// Event triggered when health reaches zero
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCombatDeath);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CITA417_LAB08_API UCombatHealthComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UCombatHealthComponent();

    // Maximum health of the target
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
    float MaxHealth = 100.0f;

    // Current health of the target
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
    float CurrentHealth = 100.0f;

    // Whether the target is dead
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
    bool bIsDead = false;

    // Called when the target receives damage
    UFUNCTION(BlueprintCallable, Category = "Health")
    void TakeDamage(float DamageAmount);

    // Event triggered when health reaches zero
    UPROPERTY(BlueprintAssignable, Category = "Health")
    FOnCombatDeath OnDeath;

protected:
    virtual void BeginPlay() override;
};
