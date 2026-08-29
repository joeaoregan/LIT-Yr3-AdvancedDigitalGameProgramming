# Game State Machine Architecture

The `GameStateMachine` handles the flow of the Alien Attack application by transitioning between different interactive states, such as the main menu, active gameplay, and game over screens.

## Core Components

* [GameState.h](https://github.com/joeaoregan/LIT-Yr3-AdvancedDigitalGameProgramming/blob/master/1-AlienAttack/Alien%20Attack%20K00203642/GameState.h): An abstract base class that establishes the contract for all specific game states (e.g., `PlayState`, `MenuState`, `PauseState`, `GameOverState`). It requires implementations for standard lifecycle functions like `update()`, `render()`, `onEnter()`, and `onExit()`.
* [GameStateMachine.h](https://github.com/joeaoregan/LIT-Yr3-AdvancedDigitalGameProgramming/blob/master/1-AlienAttack/Alien%20Attack%20K00203642/GameStateMachine.h) & [GameStateMachine.cpp](https://github.com/joeaoregan/LIT-Yr3-AdvancedDigitalGameProgramming/blob/master/1-AlienAttack/Alien%20Attack%20K00203642/GameStateMachine.cpp): The manager class that maintains a stack of currently active game states.

## State Management

The state machine is used to control the active scene through three primary methods:

* **`pushState(GameState* state)`**: Adds a new state to the top of the stack without destroying the previous state. This approach is ideal for overlay screens, such as adding a `PauseState` on top of the `PlayState`.
* **`popState()`**: Removes the current state from the top of the stack, triggering its `onExit()` method, and resumes the previous state underneath it.
* **`changeState(GameState* state)`**: Replaces the currently active state entirely. It calls `onExit()` on the outgoing state, removes it, and then calls `onEnter()` on the new incoming state.

## Execution Flow

During the main application loop, the core `Game` class delegates logic and drawing responsibilities to the `GameStateMachine`. The machine then calls the `update()` and `render()` functions exclusively for the active state currently residing at the top of the stack.