# Level Objective State

The `LevelObjectiveState` class represents the mission briefing and objective display interface within the Alien Attack project. Inheriting from the base [GameState](game.md) class, it presents stage goals and requirements to the player before gameplay begins.

## Core Components

* [LevelObjectiveState.h](https://github.com/joeaoregan/LIT-Yr3-AdvancedDigitalGameProgramming/blob/master/1-AlienAttack/Alien%20Attack%20K00203642/LevelObjectiveState.h) & [LevelObjectiveState.cpp](https://github.com/joeaoregan/LIT-Yr3-AdvancedDigitalGameProgramming/blob/master/1-AlienAttack/Alien%20Attack%20K00203642/LevelObjectiveState.cpp): The concrete implementation files that define the layout and behavior of the objective briefing screen.

## Key Responsibilities

* **Briefing Display**: Renders descriptive text and UI elements outlining the specific goals required to complete the upcoming stage.
* **Input Management**: Coordinates with the [InputHandler](../architecture/input-handler.md) to detect when the player acknowledges the objectives and chooses to proceed.
* **State Management**: Communicates with the [GameStateMachine](../architecture/state-machine.md) to transition smoothly from the briefing screen into the active [Play State](play.md).

## Related States

* [Main Menu State](main-menu.md)
* [Play State](play.md)