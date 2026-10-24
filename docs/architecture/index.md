# Game Architecture

![Alien Attack System Architecture](../images/svg/game_architecture.svg)

The Alien Attack architecture follows a decoupled, data-driven design pattern built on top of SDL 2.0. The engine is divided into distinct subsystems: an abstracted input polling layer, a stack-based finite state machine, a dynamic data-driven level and entity factory, and a categorised collision resolution engine.

!!! tip "Architectural Decoupling"  
    * **State Stack**: Gameplay states (e.g. `PlayState`, `PauseState`) are managed dynamically via `pushState()` and `popState()` without destroying background scenes.
    * **Data-Driven Spawning**: Stage layouts are authored externally in Tiled XML files and parsed at runtime by `LevelParser`, communicating with `GameObjectFactory` to instantiate entities via string IDs without hardcoding C++ classes into the map parser.
    * **Layered Collisions**: `CollisionManager` evaluates interactions between discrete entity groups (player projectiles vs enemies, enemy fire vs player) rather than performing costly all-pairs checks.

---

## Core Engine Subsystems

* **[Game State Machine](state-machine.md)**  
  Manages application lifecycle and scenes via a stack of `GameState` pointers (`pushState`, `popState`, `changeState`).
* **[Game Object Factory](object-factory.md)**  
  Singleton registry mapping string type IDs to concrete object creator functions.
* **[Level Parser](level-parser.md)**  
  Decodes external Tiled XML stage maps into tilesets, collision layers, and spawned entity lists.
* **[Play State](play-state.md)**  
  The primary gameplay orchestrator managing the level, player instance, and active object collections.
* **[Collision Manager](collision-manager.md)**  
  Performs Axis-Aligned Bounding Box (AABB) checks across categorised entity groups.
* **[Input Handler](input-handler.md)**  
  Abstracts raw SDL keyboard, gamepad, and mouse events into game velocity vectors and fire actions.
* **[Bullet Handler](bullet-handler.md)**  
  Manages projectile pools and movement physics for both the player and hostile forces.

---

## User Interface & Presentation Subsystems

* **[Heads Up Display (HUD)](hud.md)**  
  Overlays active player health, remaining lives, and current high score onto the screen.
* **[Mini Map](mini-map.md)**  
  Renders a scaled radar overview of the active stage, showing player progression and incoming enemy waves.
* **[Animated Graphics](animated-graphics.md)**  
  Handles looped explosion particle sequences and transient destruction effects.
