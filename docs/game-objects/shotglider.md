# ShotGlider Object

The `ShotGlider` class represents an armed enemy variant within the Alien Attack project. Inheriting from the base [Enemy](enemy.md) class, it expands upon standard glider behaviours by introducing the ability to fire projectiles at the player.

## Core Components

* [ShotGlider.h](https://github.com/joeaoregan/LIT-Yr3-AdvancedDigitalGameProgramming/blob/master/1-AlienAttack/Alien%20Attack%20K00203642/ShotGlider.h): The concrete class files defining the specific properties of the ShotGlider, such as its firing rate, projectile type, and flight trajectory.

## Key Responsibilities

* **Combat and Movement**: Instead of merely flying across the screen, the `ShotGlider` periodically interacts with the [BulletHandler](../architecture/bullet-handler.md) to spawn hostile projectiles. Its `update()` method calculates both its movement path and its weapon cooldown timers.
* **Factory Registration**: The class registers a unique string identifier with the [GameObjectFactory](../architecture/object-factory.md). This is used to make certain the [LevelParser](../architecture/level-parser.md) can dynamically instantiate the object when reading level data.
* **Collision Response**: It relies on inherited methods to process damage from player attacks, triggering an `AnimatedGraphic` explosion and awarding points when its health reaches zero.