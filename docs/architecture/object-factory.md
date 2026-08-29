# GameObjectFactory Architecture

The `GameObjectFactory` is a core component of the game engine used to instantiate different types of game entities dynamically. Instead of hardcoding object creation throughout the codebase, the factory uses string identifiers to spawn objects, which is essential for loading levels dynamically from data files.

## Core Components

* [GameObject.h](https://github.com/joeaoregan/LIT-Yr3-AdvancedDigitalGameProgramming/blob/master/1-AlienAttack/Alien%20Attack%20K00203642/GameObject.h): The abstract base class for all entities in the game. All objects spawned by the factory must inherit from this class to guarantee a standard interface.
* [GameObjectFactory.h](https://github.com/joeaoregan/LIT-Yr3-AdvancedDigitalGameProgramming/blob/master/1-AlienAttack/Alien%20Attack%20K00203642/GameObjectFactory.h) & [GameObjectFactory.cpp](https://github.com/joeaoregan/LIT-Yr3-AdvancedDigitalGameProgramming/blob/master/1-AlienAttack/Alien%20Attack%20K00203642/GameObjectFactory.cpp): A singleton class that maintains a registry of object types (typically an `std::map`) mapping string identifiers to their corresponding creator functions or classes.

## Registration and Creation Process

The factory pattern operates in two main phases to make certain objects are generated correctly:

1. **Registration:** Each specific game object class (such as [Player](../game-objects/player.md), [Glider](../game-objects/glider.md), or [Bullet](../game-objects/bullet.md)) registers a unique string ID (e.g., `"Player"`) with the [GameObjectFactory](object-factory.md) alongside a specific creator object or function. This typically happens at the start of the game or when a level is initialised.
2. **Instantiation:** When the map or level loader reads a data file, it extracts string IDs for various entities. It then passes this ID to the `GameObjectFactory`, which looks up the ID in its registry and uses the associated creator to spawn the correct object in memory.

## Benefits

* **Decoupling:** The level parsing logic does not need to know about every specific game object class. It only needs to interface with the base [GameObject](../game-objects/index.md) class and the [GameObjectFactory](object-factory.md).
* **Extensibility:** Adding a new enemy or item type only requires creating the new class and registering its ID with the factory. The core level loading code remains completely unchanged.