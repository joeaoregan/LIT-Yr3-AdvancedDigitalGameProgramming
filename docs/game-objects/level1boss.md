# Level 1 Boss Object

The `Level1Boss` class represents the climactic enemy encounter at the end of the first stage within the Alien Attack project. Inheriting from the base [Enemy](enemy.md) class, it features a significantly higher health pool and more complex behaviours compared to standard hostile units.

## Core Components

* [Level1Boss.h](https://github.com/joeaoregan/LIT-Yr3-AdvancedDigitalGameProgramming/blob/master/1-AlienAttack/Alien%20Attack%20K00203642/Level1Boss.h): The class header file defining the specific properties of the boss, including its attack patterns, health thresholds, and unique animation frames.

## Key Responsibilities

* **Advanced Combat and Movement**: Instead of a simple flight path, the boss uses its `update()` method to execute complex movement phases and attack patterns, heavily interacting with the [BulletHandler](../architecture/bullet-handler.md) to challenge the player.
* **Factory Registration**: The class registers a unique string identifier with the [GameObjectFactory](../architecture/object-factory.md). This is used to make certain the [LevelParser](../architecture/level-parser.md) can dynamically instantiate the boss when reading the end of the map data.
* **Collision and Progression**: It relies on inherited methods to process damage from the player's attacks. When its health is finally depleted, its destruction sequence is used to signal the `PlayState` to transition into the `LevelCompleteState`.