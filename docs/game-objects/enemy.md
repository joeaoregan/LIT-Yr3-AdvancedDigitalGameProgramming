# Enemy Object

The `Enemy` class serves as the base template for all hostile units within the Alien Attack project. Inheriting from the [GameObject](index.md) base class, it establishes the shared behaviours and properties used by specific enemy variants.

## Core Components

* [Enemy.h](https://github.com/joeaoregan/LIT-Yr3-AdvancedDigitalGameProgramming/blob/master/1-AlienAttack/Alien%20Attack%20K00203642/Enemy.h): The base class defining common hostile logic, such as health tracking, generic collision responses, and screen boundary checks.

## Key Responsibilities

* **Movement Patterns**: While the base class handles standard position updates, each subclass defines its own `update()` logic to dictate specific flight paths and movement behaviours across the screen.
* **Combat Mechanics**: Specific enemy variants interact with the [BulletHandler](../architecture/bullet-handler.md) to spawn and direct projectiles towards the player.
* **Collision and Destruction**: The class relies on the [CollisionManager](../architecture/collision-manager.md) to process damage taken from player bullets. When health reaches zero, the enemy triggers its destruction sequence, often spawning an `AnimatedGraphic` explosion and awarding points.

## Enemy Variants

Instead of a single enemy type, the project uses the `GameObjectFactory` to instantiate various distinct subclasses. These include:

* `Glider` and `ShotGlider`.
* `AngryGlider`.
* `Pounder`.
* `Eskeletor`.
* `Level1Boss`.