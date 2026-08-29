# Bullet Object

The `Bullet` class represents an individual projectile entity within the Alien Attack project. It encapsulates the specific data and movement logic required for a single shot fired by either the player or an enemy.

## Core Components

* [Bullet.h](https://github.com/joeaoregan/LIT-Yr3-AdvancedDigitalGameProgramming/blob/master/1-AlienAttack/Alien%20Attack%20K00203642/Bullet.h): The header file defining the fundamental properties of a projectile, including its velocity, damage output, and active state.

## Key Responsibilities

* **Trajectory and Movement**: The bullet manages its own positional updates each frame based on its assigned directional velocity.
* **Faction Identification**: The object maintains properties to identify its origin. This distinction is used by the [CollisionManager](../architecture/collision-manager.md) to make certain projectiles only interact with valid targets from the opposing faction.
* **Lifecycle Flagging**: Instead of handling its own memory destruction, the bullet tracks its position relative to the screen boundaries. Once it travels out of bounds or strikes a target, it flags itself as inactive so the [BulletHandler](../architecture/bullet-handler.md) can safely remove it from the active game loop.