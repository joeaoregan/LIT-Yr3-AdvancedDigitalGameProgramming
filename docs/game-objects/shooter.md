# Shooter Object

The `ShooterObject` class serves as an intermediate base class for entities capable of firing projectiles within the Alien Attack project. Inheriting from the core [GameObject](index.md) class, it extends base entity functionality by incorporating weapon handling logic and shooting attributes.

## Core Components

* [ShooterObject.h](https://github.com/joeaoregan/LIT-Yr3-AdvancedDigitalGameProgramming/blob/master/1-AlienAttack/Alien%20Attack%20K00203642/ShooterObject.h) & [ShooterObject.cpp](https://github.com/joeaoregan/LIT-Yr3-AdvancedDigitalGameProgramming/blob/master/1-AlienAttack/Alien%20Attack%20K00203642/ShooterObject.cpp): The concrete implementation files that establish shared variables and functions for shooting entities, such as ammunition tracking, firing cooldowns, and projectile velocities.

## Key Responsibilities

* **Projectile Spawning**: The class provides foundational logic to interface with the [BulletHandler](../architecture/bullet-handler.md), allowing derived entities to spawn and project ammunition consistently into the game world.
* **State Management**: It maintains timers and state flags to regulate fire rates, preventing entities from continuously firing without delay.
* **Inheritance Hierarchies**: Acts as a bridge between the generic [GameObject](index.md) base class and more complex armed entities like the [Player](player.md) or specialized armed enemies, reducing code duplication across weapon-equipped objects.