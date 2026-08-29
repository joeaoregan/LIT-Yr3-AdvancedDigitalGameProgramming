# Glider Object

The `Glider` class represents a specific enemy variant within the Alien Attack project. Inheriting from the base [Enemy](enemy.md) class, it defines the unique flight patterns and behaviours characteristic of this standard hostile unit.

## Core Components

* [Glider.h](https://github.com/joeaoregan/LIT-Yr3-AdvancedDigitalGameProgramming/blob/master/1-AlienAttack/Alien%20Attack%20K00203642/Glider.h): The concrete class files defining the Glider's specific properties, such as its starting health, animation frames, and movement velocity.

## Key Responsibilities

* **Movement Logic**: Instead of following a complex, multi-stage path, the Glider typically implements a straightforward, sweeping flight pattern across the screen. Its `update()` method calculates this continuous trajectory.
* **Factory Registration**: To allow dynamic level loading, the Glider registers its specific string identifier with the `GameObjectFactory`. This is used to make certain the [LevelParser](../architecture/level-parser.md) can spawn Gliders directly from parsed map data.
* **Collision Response**: It relies on the inherited [Enemy](enemy.md) and base [GameObject](index.md) methods to process damage from player projectiles. When its health is depleted, it triggers a destruction sequence, usually spawning an `AnimatedGraphic` explosion.