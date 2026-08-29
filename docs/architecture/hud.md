# HUD Architecture

The `HUD` (Heads Up Display) component is responsible for presenting real-time game metrics and visual feedback to the player during the active gameplay phase.

## Core Components

* [HUD.h](https://github.com/joeaoregan/LIT-Yr3-AdvancedDigitalGameProgramming/blob/master/1-AlienAttack/Alien%20Attack%20K00203642/HUD.h): The dedicated class files that manage the layout, updating, and rendering of the interface elements overlaying the main game screen.

## Interface Management

* **Metric Tracking**: The HUD continuously monitors the game state to extract vital statistics, such as the player's current score, health points, and remaining lives.
* **Visual Rendering**: Instead of embedding text rendering and UI drawing directly within the `PlayState` or [Player](../game-objects/player.md) classes, the `HUD` is used to cleanly overlay these elements on top of the `Level` and active entities.
* **Separation of Concerns**: By placing the UI logic into its own class, the architecture is designed to make certain that interface updates do not interfere with core collision or movement logic.

## Execution and Usage

During the gameplay loop, the `PlayState` calls the `HUD`'s update and render methods after processing the main entities. This specific rendering order is used to make certain the interface is drawn last, placing it securely on top of the scrolling background and active game objects.