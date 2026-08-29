# PowerUp Object

The `PowerUp` class represents a collectible enhancement entity within the Alien Attack project. Inheriting from the base [GameObject](index.md) class, it provides the player with specific benefits, such as health restoration or weapon upgrades, upon successful collection.

## Core Components

* [PowerUp.h](https://github.com/joeaoregan/LIT-Yr3-AdvancedDigitalGameProgramming/blob/master/1-AlienAttack/Alien%20Attack%20K00203642/PowerUp.h): The class header file defining the specific properties of the power-up, including its drop velocity, visual animation frames, and the exact type of enhancement it grants.

## Key Responsibilities

* **Movement Logic**: Instead of executing complex flight patterns, the `PowerUp` typically uses its `update()` method to scroll or fall predictably across the screen, giving the player an opportunity to intercept it.
* **Factory Registration**: The class registers a unique string identifier with the [GameObjectFactory](../architecture/object-factory.md). This is used to make certain the engine can dynamically instantiate the object, whether it is spawned directly by the [LevelParser](../architecture/level-parser.md) from map data or dropped dynamically by a defeated enemy.
* **Collision and Collection**: It relies on the [CollisionManager](../architecture/collision-manager.md) to detect when the player's bounding box intersects with it. Upon a verified collision, it applies its designated benefit to the player and immediately flags itself for removal to prevent multiple collections.