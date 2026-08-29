# Game State

The `GameState` class serves as an abstract base class for all operational scenes and menus within the Alien Attack project. It establishes a uniform interface that the [GameStateMachine](../architecture/state-machine.md) uses to manage screen transitions, updates, and rendering loops.

## Core Components

* [GameState.h](https://github.com/joeaoregan/LIT-Yr3-AdvancedDigitalGameProgramming/blob/master/1-AlienAttack/Alien%20Attack%20K00203642/GameState.h): The header file defining the pure virtual interface required for all concrete game states.

## Key Responsibilities

* **Lifecycle Management**: Mandates standard virtual methods such as `update()`, `render()`, `onEnter()`, and `onExit()` to handle state activation, runtime logic, drawing routines, and cleanup.
* **State Identification**: Requires a pure virtual `getStateID()` function, returning a unique string identifier used by the state machine to track and switch between active screens.
* **Polymorphic Control**: Allows the [GameStateMachine](../architecture/state-machine.md) to execute state logic uniformly without needing to know the specific implementation details of individual menus or levels.

## Related States

* [Main Menu State](main-menu.md)
* [Play State](play.md)
* [Pause State](pause.md)
* [Game Over State](game-over.md)