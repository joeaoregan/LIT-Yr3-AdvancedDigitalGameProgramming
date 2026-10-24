# Game Objects

![Alien Attack Entity Inheritance &amp; Hierarchy](../images/svg/entity_hierarchy.svg)

The Alien Attack entity architecture is constructed around an object-oriented inheritance hierarchy rooted in the abstract `GameObject` base class. Rather than managing disparate collections for each entity type, the game loop and level layers process entities polymorphically through common lifecycle and transformation interfaces.

!!! tip "Polymorphic Hierarchy"  
    * **Uniform Lifecycle**: Every interactive entity adheres to the standard `load()`, `update()`, `draw()`, `collision()`, and `clean()` virtual methods.
    * **Kinematic Inheritance**: `ShooterObject` extends the root base class with 2D Newtonian velocity vectors (`Vector2D`), projectile weapon cooldown timers, death animation routines, and on-screen health bar (`StatusBar`) rendering.
    * **Factory Integration**: Concrete entity classes register unique string identifiers with `GameObjectFactory`, allowing external Tiled level files to spawn diverse player, enemy, projectile, and pickup objects dynamically.

---

## Architecture Layers

* **[GameObject](https://github.com/joeaoregan/LIT-Yr3-AdvancedDigitalGameProgramming/blob/master/1-AlienAttack/Alien%20Attack%20K00203642/GameObject.h)**  
  The root abstract base class defining standard spatial coordinates, bounding box metrics, collision callbacks, and scrolling physics.
* **[Shooter Object](shooter.md)**  
  The primary intermediate subclass providing combat infrastructure, weapon fire cooldown counters, death sound triggers, and health bar overlays.

---

## Entity Categories

### Player & Weapon Systems
Entities dedicated to player movement, weapon fire, and combat upgrades:

* **[Player](player.md)**  
  The user-controlled ship incorporating input abstraction, dual-weapon firing modes, and boundary observer tracking.
* **[Bullet](bullet.md)**  
  High-speed linear projectiles partitioned into friendly (`PlayerBullet`) and hostile (`EnemyBullet`) pools.
* **[Power Up](powerup.md)**  
  Collectible items dropped by downed enemies that replenish shields or upgrade weapon spread.

### Hostile Enemy Roster
Autonomous adversaries deriving from the common `Enemy` base class:

* **[Enemy](enemy.md)**  
  The base class for all hostile craft, managing hit point thresholds, point yields, and firing triggers.
* **[Glider](glider.md)**  
  Standard scouting vessel executing a smooth sinusoidal wave flight pattern.
* **[Shot Glider](shotglider.md)**  
  Armed variant of the Glider that unleashes targeted projectiles toward the player.
* **[Angry Glider](angryglider.md)**  
  Aggressive, high-velocity variant that charges directly toward player coordinates.
* **[Pounder](pounder.md)**  
  Heavy vertical hazard that crashes downward to crush passing ships.
* **[Eskeletor](eskeletor.md)**  
  Ground-walking mechanical unit navigating horizontal surface terrain.
* **[Roof Turret](roof-turret.md)**  
  Ceiling-mounted automated defense battery with 360-degree rotational tracking.
* **[Level 1 Boss](level1boss.md)**  
  Multi-stage capital ship featuring escort wave spawning, invulnerability shields, and phased attack patterns.
