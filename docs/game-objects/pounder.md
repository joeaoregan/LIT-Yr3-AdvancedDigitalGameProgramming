# Pounder Object

The `Pounder` class represents a heavy enemy variant within the Alien Attack project. Inheriting from the base [Enemy](enemy.md) class, it introduces unique movement mechanics, typically characterised by hovering and rapid vertical dropping attacks.

## Core Components

* [Pounder.h](https://github.com/joeaoregan/LIT-Yr3-AdvancedDigitalGameProgramming/blob/master/1-AlienAttack/Alien%20Attack%20K00203642/Pounder.h): The class header file defining the specific properties of the Pounder, such as its vertical velocity, drop triggers, and animation states.

## Key Responsibilities

* **Movement Logic**: Instead of standard horizontal sweeping, the `Pounder` is used to implement a plunging or dropping flight pattern within its `update()` method to catch the player off guard.
* **Factory Registration**: The class registers a unique string identifier with the [GameObjectFactory](../architecture/object-factory.md). This is used to make certain the [LevelParser](../architecture/level-parser.md) can dynamically instantiate the object when reading map data.
* **Collision Response**: It relies on inherited methods to process damage from player attacks, triggering an `AnimatedGraphic` explosion and awarding points when its health is depleted.