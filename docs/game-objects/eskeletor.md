# Eskeletor Object

The `Eskeletor` class represents a specific enemy variant within the Alien Attack project. Inheriting from the base [Enemy](enemy.md) class, it introduces distinct visual characteristics and movement mechanics to further diversify the hostile encounters.

## Core Components

* [Eskeletor.h](https://github.com/joeaoregan/LIT-Yr3-AdvancedDigitalGameProgramming/blob/master/1-AlienAttack/Alien%20Attack%20K00203642/Eskeletor.h): The class header file defining the specific properties of the Eskeletor, such as its assigned sprite frames, starting health, and flight velocity.

## Key Responsibilities

* **Movement Logic**: Instead of sharing the exact flight path of standard gliders, the `Eskeletor` uses its `update()` method to execute its own unique trajectory or behaviour on the screen.
* **Factory Registration**: The class registers a unique string identifier with the [GameObjectFactory](../architecture/object-factory.md). This is used to make certain the [LevelParser](../architecture/level-parser.md) can dynamically instantiate the object when reading map data.
* **Collision Response**: It relies on inherited methods to process damage from player attacks, triggering an `AnimatedGraphic` explosion and awarding points when its health is depleted.