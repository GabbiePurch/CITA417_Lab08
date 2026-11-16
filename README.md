# CITA 417 – Lab 08 & Lab 09

## Project Overview

This project was developed in Unreal Engine 5.8 using C++ and Blueprints for CITA 417. It demonstrates character movement, animation systems, weapon firing, collision detection, and health management.

## Features

### Character Movement
- Third-person character movement and jumping.
- Sprinting using the Enhanced Input System.
- C++ movement variables exposed to Blueprints.

### Animation System
- Animation Blueprint with idle, walking, running, jumping, and falling states.
- Animation State Machine driven by C++ character variables.
- Firing animation implemented using an Animation Montage.
- Layered animation blending allows the character to move while firing.

### Combat System
- C++ weapon class (`ACombatWeapon`).
- Left mouse button triggers weapon firing.
- Line tracing for hit detection.
- Debug lines visualize successful hits and misses.
- Weapon cooldown and configurable attack damage.
- MuzzlePoint component attached to the character's hand.

### Health and Damage
- Custom C++ health component (`UCombatHealthComponent`).
- Damageable cube and sphere targets.
- Each successful shot applies damage to the target.
- Targets are destroyed when their health reaches zero.
- Unreal Engine Output Log displays damage and hit information.

## Controls

| Input | Action |
|---|---|
| W, A, S, D | Move |
| Mouse | Look around |
| Space | Jump |
| Left Shift | Sprint |
| Left Mouse Button | Fire weapon |

## Technologies Used

- Unreal Engine 5.8
- C++
- Unreal Engine Blueprints
- Enhanced Input System
- Animation Blueprints and Montages
- Visual Studio Community 2026

## Testing

The project was tested to verify character movement, sprinting, jumping, animation transitions, weapon firing, hit detection, damage application, and target destruction.

## Author

Gabbie Purchiaroni

SUNY Morrisville – CITA 417



## Combat Architecture

```text
Player Input (Left Mouse Button)
             |
             v
Character (ACITA417_Lab08Character)
             |
             v
Weapon Actor (ACombatWeapon)
             |
             v
Line Trace / Hit Detection
             |
             v
Target Actor (Cube or Sphere)
             |
             v
Health Component (UCombatHealthComponent)
             |
             v
Damage Applied / Health Reduced
             |
             v
Health Reaches Zero?
             |
             v
OnDeath Event → Target Destroyed
```

### Reusability

If a destructible crate were added to the project, the existing `ACombatWeapon` would not need to be modified.

The crate could reuse the `UCombatHealthComponent` to receive damage, track health, and trigger an event when health reaches zero. The crate would only need its own death behavior, such as destruction or a breaking animation.

This architecture separates attack logic from health and damage management, allowing different objects to use the same combat system.

### Independent Improvement

An attack cooldown was implemented in `ACombatWeapon` to prevent firing continuously without a delay.

The weapon checks the elapsed time since the previous attack before allowing another shot. This adds controlled firing behavior without duplicating combat logic in the Player Character.
