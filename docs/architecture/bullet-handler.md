# BulletHandler Architecture

The `BulletHandler` is responsible for managing the lifecycle, updating, and rendering of all projectile entities within the Alien Attack project. By centralising projectile management, it keeps the main game loop and individual entity classes free from bullet tracking logic.

## Core Components

* [Bullet.h](https://github.com/joeaoregan/LIT-Yr3-AdvancedDigitalGameProgramming/blob/master/1-AlienAttack/Alien%20Attack%20K00203642/Bullet.h): The base definition for a projectile object, containing properties such as velocity, damage, and heading.
* [BulletHandler.h](https://github.com/joeaoregan/LIT-Yr3-AdvancedDigitalGameProgramming/blob/master/1-AlienAttack/Alien%20Attack%20K00203642/BulletHandler.h) & [BulletHandler.cpp](https://github.com/joeaoregan/LIT-Yr3-AdvancedDigitalGameProgramming/blob/master/1-AlienAttack/Alien%20Attack%20K00203642/BulletHandler.cpp): A dedicated manager class that stores active bullets in memory and updates their state every frame.

## Projectile Management

* **Separation of Factions**: The handler typically maintains separate lists or vectors for player bullets and enemy bullets. This separation is used to optimise collision detection, making certain that player bullets only check for impacts against enemies, and vice versa.
* **Lifecycle Control**: When a player or enemy fires a weapon, they register a new bullet with the `BulletHandler`. The handler then takes over, updating the bullet's trajectory across the screen.
* **Cleanup**: To prevent memory leaks, the handler monitors the position of each active bullet. If a bullet collides with a valid target or travels outside the predefined screen boundaries, the handler safely destroys it and removes it from the active list.

## Execution and Usage

During the `PlayState` update loop, the `BulletHandler` iterates through all active projectiles to update their positions. It is then accessed by the [CollisionManager](collision-manager.md) to verify if any of these updated positions intersect with valid targets. Finally, the handler's render function draws all active bullets to the screen.