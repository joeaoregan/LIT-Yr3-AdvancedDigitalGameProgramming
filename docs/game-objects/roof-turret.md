# RoofTurret Object

The `RoofTurret` class represents a stationary defensive enemy structure positioned on level surfaces within the Alien Attack project. Inheriting from the base `ShooterObject` or [Enemy](enemy.md) class, it targets the player from fixed positions.

## Core Components

* [RoofTurret.h](https://github.com/joeaoregan/LIT-Yr3-AdvancedDigitalGameProgramming/blob/master/1-AlienAttack/Alien%20Attack%20K00203642/RoofTurret.h): The class header file defining the specific properties of the turret, including its targeting angles, firing intervals, and health status.

## Key Responsibilities

* **Stationary Targeting**: Unlike mobile enemy units that traverse the screen, the `RoofTurret` remains fixed to environmental geometry. Its `update()` method focuses on tracking the player's position or maintaining a steady firing rhythm.
* **Combat Mechanics**: The turret interacts with the [BulletHandler](../architecture/bullet-handler.md) to periodically spawn hostile projectiles aimed at the player.
* **Factory Registration**: The class registers a unique string identifier with the [GameObjectFactory](../architecture/object-factory.md). This allows the [LevelParser](../architecture/level-parser.md) to dynamically place stationary turrets directly from parsed map layouts.
* **Collision and Destruction**: It relies on the `CollisionManager` to process damage from player attacks. When its health is depleted, it triggers a destruction animation via an `AnimatedGraphic` and awards points.