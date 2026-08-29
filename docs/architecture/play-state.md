# PlayState Architecture

The `PlayState` is the core interactive phase of the Alien Attack game where the primary gameplay loop occurs. It inherits from the base `GameState` class and manages the active level, player input, entities, and collision detection.

## Core Components

* [PlayState.h](https://github.com/joeaoregan/LIT-Yr3-AdvancedDigitalGameProgramming/blob/master/1-AlienAttack/Alien%20Attack%20K00203642/PlayState.h) & [PlayState.cpp](https://github.com/joeaoregan/LIT-Yr3-AdvancedDigitalGameProgramming/blob/master/1-AlienAttack/Alien%20Attack%20K00203642/PlayState.cpp): Contains the specific implementation for the gameplay phase, adhering to the standard state lifecycle functions.
* **Entity Management**: Handles the active `Level` instance, which in turn manages layers and parsed [GameObject](../game-objects/index.md) instances like the [Player](../game-objects/player.md) and various [Enemy](../game-objects/enemy.md) subclasses.
* **Handlers**: Interacts with the [CollisionManager](collision-manager.md) to detect impacts between the player, enemies, and bullets. Bullets are managed via a dedicated [BulletHandler](bullet-handler.md), while the [HUD](hud.md) is updated to display the current score and player status.

## State Lifecycle

1. **`onEnter()`**: Initialises the level by invoking the [LevelParser](level-parser.md), loads required textures, and spawns the player alongside the initial wave of enemies.
2. **`update()`**: Iterates through all active game objects, processes input via the [InputHandler](input-handler.md), updates positions, and triggers the [CollisionManager](collision-manager.md). If the pause button is pressed, it signals the [GameStateMachine](state-machine.md) to push the `PauseState`. If the player loses all health, it transitions to the `GameOverState`. Upon beating the level boss, it transitions to the `LevelCompleteState`.
3. **`render()`**: Draws the `ScrollingBackground`, level tiles, all active dynamic entities, and the HUD to the screen.
4. **`onExit()`**: Cleans up memory, clears out entities, and frees textures used exclusively during the active gameplay phase.