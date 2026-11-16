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
