# Pause State

The `PauseState` class represents the gameplay suspension interface within the Alien Attack project. Inheriting from the base [GameState](game.md) class, it manages the temporary halting of active sessions, presenting options for the player to resume gameplay or return to the main menu.

## Core Components

* [PauseState.h](https://github.com/joeaoregan/LIT-Yr3-AdvancedDigitalGameProgramming/blob/master/1-AlienAttack/Alien%20Attack%20K00203642/PauseState.h) & [PauseState.cpp](https://github.com/joeaoregan/LIT-Yr3-AdvancedDigitalGameProgramming/blob/master/1-AlienAttack/Alien%20Attack%20K00203642/PauseState.cpp): The concrete implementation files that define the layout and control flow of the pause overlay.

## Key Responsibilities

* **Menu Navigation**: Instantiates buttons that register user selections via the [InputHandler](../architecture/input-handler.md) to toggle back to active play or exit out of the session.
* **State Management**: Coordinates with the [GameStateMachine](../architecture/state-machine.md) to pop the pause state off the active stack, returning execution cleanly to the [Play State](play.md).
* **Resource Control**: Handles activation and deactivation steps via `onEnter()` and `onExit()` to manage menu assets and screen overlay rendering without destroying underlying gameplay data.

## Related States

* [Main Menu State](main-menu.md)
* [Play State](play.md)
* [Settings State](settings.md)