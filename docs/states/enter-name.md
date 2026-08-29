# Enter Name State

The `EnterNameState` class represents the player name input interface within the Alien Attack project. Inheriting from the base [GameState](game.md) class, it provides a screen where players can record their name for high score tracking following a game session.

## Core Components

* [EnterNameState.h](https://github.com/joeaoregan/LIT-Yr3-AdvancedDigitalGameProgramming/blob/master/1-AlienAttack/Alien%20Attack%20K00203642/EnterNameState.h) & [EnterNameState.cpp](https://github.com/joeaoregan/LIT-Yr3-AdvancedDigitalGameProgramming/blob/master/1-AlienAttack/Alien%20Attack%20K00203642/EnterNameState.cpp): The concrete implementation files that define the layout, text input capture, and behavior of the name entry screen.

## Key Responsibilities

* **Input Handling**: Interfaces with the [InputHandler](../architecture/input-handler.md) to capture keyboard inputs, allowing players to type their name into the prompt.
* **State Management**: Communicates with the [GameStateMachine](../architecture/state-machine.md) to save the entered name and transition the user forward to the [High Score State](high-score.md) or back to the [Main Menu State](main-menu.md).
* **Lifecycle Control**: Manages the initialization and cleanup of input UI assets via `onEnter()` and `onExit()` methods.

## Related States

* [Main Menu State](main-menu.md)
* [High Score State](high-score.md)