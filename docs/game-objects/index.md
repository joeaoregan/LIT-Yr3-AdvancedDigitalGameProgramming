# Game Objects

The `GameObject` acts as the fundamental abstract base class for all entities within the [Alien Attack project](https://github.com/joeaoregan/LIT-Yr3-AdvancedDigitalGameProgramming/tree/master/1-AlienAttack/Alien%20Attack%20K00203642). It establishes a common interface and shared properties that all interactive elements must implement to function within the game loop.

## Core Components

* [GameObject.h](https://github.com/joeaoregan/LIT-Yr3-AdvancedDigitalGameProgramming/blob/master/1-AlienAttack/Alien%20Attack%20K00203642/GameObject.h): The header file defining the abstract base class. It dictates the standard lifecycle functions that any derived entity is required to have.

## Interface and Lifecycle

* **Standardised Methods**: The class mandates core virtual functions such as `update()`, `draw()`, and `clean()`. The main game loop calls these functions on all active entities, allowing the engine to process and render them seamlessly.
* **Shared Properties**: While the specific implementation is left to derived classes, the base interface is used to manage standard spatial attributes like X and Y coordinates, width, and height.
* **Polymorphism**: Instead of managing separate lists for different entity types, the `PlayState` and `Level` classes can maintain a single collection of `GameObject` pointers. This design pattern is used to make certain the core engine remains clean and scalable, as it does not need to know the exact subclass of each object it processes.

## Derived Entities

This base architecture is extended by concrete classes to define unique behaviours. For detailed implementations, refer to the specific entity documentation:  

- [Player](player.md)
- [Enemy](enemy.md)
- [Glider](glider.md)
- [Shot Glider](shotglider.md)
- [Angry Glider](angryglider.md)
- [Eskeletor](eskeletor.md)
- [Level 1 Boss](level1boss.md)
- [Pounder](pounder.md)
- [Bullet](bullet.md)
- [Power Up](powerup.md)
- [Roof Turret](roof-turret.md)
- [Shooter Object](shooter.md)