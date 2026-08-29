# Level Complete State

The `LevelCompleteState` class represents the transition screen displayed when a player successfully clears a stage within the Alien Attack project. Inheriting from the base [GameState](game.md) class, it manages the layout, user interactions, and options presented upon completing a level.

## Core Components

* [LevelCompleteState.h](https://github.com/joeaoregan/LIT-Yr3-AdvancedDigitalGameProgramming/blob/master/1-AlienAttack/Alien%20Attack%20K00203642/LevelCompleteState.h) & [LevelCompleteState.cpp](https://github.com/joeaoregan/LIT-Yr3-AdvancedDigitalGameProgramming/blob/master/1-AlienAttack/Alien%20Attack%20K00203642/LevelCompleteState.cpp): The concrete implementation files that define the appearance and behaviour of the level completion interface.

## Key Responsibilities

* **Button Interaction**: Instantiates and tracks interactive menu options using the [InputHandler](../architecture/input-handler.md) to allow players to progress or return to the main menu.
* **State Transitions**: Communicates with the [GameStateMachine](../architecture/state-machine.md) to handle user selections, transitioning forward to subsequent stages or back to the [Main Menu State](main-menu.md).
* **Lifecycle Management**: Implements `onEnter()` and `onExit()` to load stage-specific completion UI resources and clean them up when switching states.

## Related States

* [Main Menu State](main-menu.md)
* [Play State](play.md)
* [Game Over State](game-over.md)