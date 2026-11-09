# CITA417_Lab08

# CITA 417 — Lab 08
## Character State & Animation Architecture

### Project Overview

This project was developed in Unreal Engine 5.8 using C++ and Blueprints. The goal was to create a reusable character animation system that separates gameplay logic from animation decisions.

The character supports idle, walking, running, jumping, falling, landing, and sprinting animations.

### Architecture Diagram

```text
C++ Character (CITA417_Lab08Character)
    |
    |-- MovementSpeed
    |-- MovementDirection
    |-- bIsAirborne
    |
    v
Animation Blueprint (ABP_LAB08Character)
    |
    |-- Animation State Machine
    |-- Locomotion Blend Space
    |-- Jump / Fall / Landing Transitions
    |
    v
Final Skeletal Animation Pose
    |
    v
Character Mesh / Rendering
```

### Architecture Explanation

The C++ Character is responsible for gameplay information such as movement speed, movement direction, and whether the character is airborne. The Animation Blueprint reads these values and determines which animations should play using a Blend Space and animation state machine. This separation allows gameplay logic to remain independent of specific animation assets and transitions. Directly calling individual animations from multiple gameplay functions would create tight coupling, making the system harder to modify, maintain, and reuse.

### Independent Improvement — Sprinting

I implemented a sprint system using Unreal Engine's Enhanced Input system and C++.

Pressing and holding Left Shift increases the character's maximum movement speed from 400 to 600. Releasing Left Shift restores the normal movement speed.

The system uses a dedicated `IA_Sprint` Input Action and updates the character's movement speed through C++. The Animation Blueprint automatically responds to the resulting speed changes through the locomotion Blend Space, without requiring gameplay code to select a specific running animation.

### Testing

The following functionality was tested successfully:

- Idle-to-walking animation transitions
- Walking and running animation blending
- Movement speed changes
- Jumping, falling, and landing animations
- Sprint activation and deactivation
- C++ compilation and Blueprint integration

### Tools Used

- Unreal Engine 5.8
- C++
- Visual Studio Community 2026
- Unreal Engine Blueprints
- Enhanced Input
- GitHub Desktop
