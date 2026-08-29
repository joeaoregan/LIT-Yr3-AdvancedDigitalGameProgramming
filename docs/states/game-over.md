# Game Over State

The `GameOverState` class represents the defeat screen interface displayed when the player loses all available lives within the Alien Attack project. Inheriting from the base [GameState](game.md) class, it manages the layout and options presented to the player upon failing a level.

## Core Components

* [GameOverState.h](https://github.com/joeaoregan/LIT-Yr3-AdvancedDigitalGameProgramming/blob/master/1-AlienAttack/Alien%20Attack%20K00203642/GameOverState.h) & [GameOverState.cpp](https://github.com/joeaoregan/LIT-Yr3-AdvancedDigitalGameProgramming/blob/master/1-AlienAttack/Alien%20Attack%20K00203642/GameOverState.cpp): The concrete implementation files that define the appearance and user controls of the game over screen.

## Key Responsibilities

* **Menu Navigation**: Instantiates interactive buttons that register player selections via the [InputHandler](../architecture/input-handler.md) to restart the game or return to the main menu.
* **State Management**: Communicates with the [GameStateMachine](../architecture/state-machine.md) to handle transitions, allowing players to jump back to the [Play State](play.md) or exit out to the [Main Menu State](main-menu.md).
* **Lifecycle Control**: Executes `onEnter()` to load game over UI assets and `onExit()` to clear them out when transitioning away from the screen.

## Related States

* [Main Menu State](main-menu.md)
* [Play State](play.md)
* [Pause State](pause.md)