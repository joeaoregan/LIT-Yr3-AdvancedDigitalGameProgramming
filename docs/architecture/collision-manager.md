# CollisionManager Architecture

The `CollisionManager` handles the detection and resolution of physical interactions between various game entities within the Alien Attack project. It isolates hit detection logic from the core game loop and individual entity classes.

## Core Components

* [Collision.h](https://github.com/joeaoregan/LIT-Yr3-AdvancedDigitalGameProgramming/blob/master/1-AlienAttack/Alien%20Attack%20K00203642/Collision.h): Defines the mathematical functions and algorithms used for collision detection, primarily focusing on Axis-Aligned Bounding Box (AABB) overlap tests between 2D rectangles.
* [CollisionManager.h](https://github.com/joeaoregan/LIT-Yr3-AdvancedDigitalGameProgramming/blob/master/1-AlienAttack/Alien%20Attack%20K00203642/CollisionManager.h) & [CollisionManager.cpp](https://github.com/joeaoregan/LIT-Yr3-AdvancedDigitalGameProgramming/blob/master/1-AlienAttack/Alien%20Attack%20K00203642/CollisionManager.cpp): The central system that iterates through lists of active game objects to check for intersections and trigger appropriate responses.

## Detection Process

* **Bounding Boxes**: The manager uses the positional data and dimensions (width and height) of objects like the [Player](../game-objects/player.md), [Enemy](../game-objects/enemy.md) subclasses, and [Bullet](../game-objects/bullet.md) instances to define active hit areas.
* **Categorised Checking**: Instead of checking every object against every other object, the manager categorises collision checks by group (e.g., Player vs. Enemy Bullets, Player Bullets vs. Enemies) to optimise performance.
* **Level Boundaries**: It interacts with map limits defined in [BoundaryStuff.h](https://github.com/joeaoregan/LIT-Yr3-AdvancedDigitalGameProgramming/blob/master/1-AlienAttack/Alien%20Attack%20K00203642/BoundaryStuff.h) to make certain entities do not move outside the playable screen area.

## Resolution

When a collision is verified, the manager resolves the interaction by applying damage, triggering state changes, or destroying the entity. This often involves spawning an `AnimatedGraphic` to display an explosion and notifying the [Player](../game-objects/player.md) or [Enemy](../game-objects/enemy.md) to update their health status.
