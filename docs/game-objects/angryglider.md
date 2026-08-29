# AngryGlider Object

The `AngryGlider` class represents an aggressive enemy variant within the Alien Attack project. Inheriting from the base [Enemy](enemy.md) class, it expands upon standard glider behaviours by introducing faster or more erratic flight patterns to challenge the player.

## Core Components

* [AngryGlider.h](https://github.com/joeaoregan/LIT-Yr3-AdvancedDigitalGameProgramming/blob/master/1-AlienAttack/Alien%20Attack%20K00203642/AngryGlider.h): The concrete class files defining the specific properties of the AngryGlider, such as increased movement velocity, unique animation frames, and aggressive behaviour.

## Key Responsibilities

* **Aggressive Movement**: Instead of a simple sweeping path, the `AngryGlider` is used to implement quicker or more unpredictable movement logic within its `update()` method.
* **Factory Registration**: The class registers a unique string identifier with the [GameObjectFactory](../architecture/object-factory.md). This is used to make certain the [LevelParser](../architecture/level-parser.md) can dynamically instantiate the object when reading map data.
* **Collision Response**: It relies on inherited methods to process damage from player attacks, triggering an `AnimatedGraphic` explosion and awarding points when its health reaches zero.