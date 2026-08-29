# Instructions State

The `InstructionsState` class represents the tutorial and control guide interface within the Alien Attack project. Inheriting from the base [GameState](game.md) class, it manages the display of gameplay rules, objective details, and control schemes to assist the player.

## Core Components

* [InstructionsState.h](https://github.com/joeaoregan/LIT-Yr3-AdvancedDigitalGameProgramming/blob/master/1-AlienAttack/Alien%20Attack%20K00203642/InstructionsState.h) & [InstructionsState.cpp](https://github.com/joeaoregan/LIT-Yr3-AdvancedDigitalGameProgramming/blob/master/1-AlienAttack/Alien%20Attack%20K00203642/InstructionsState.cpp): The concrete implementation files that define the layout and behavior of the instructions screen.

## Key Responsibilities

* **Information Display**: Renders explanatory text, UI elements, and graphical cues outlining how to pilot the player ship and engage enemy forces.
* **Input Management**: Coordinates with the [InputHandler](../architecture/input-handler.md) to listen for user dismissal commands, allowing players to exit the instructions view.
* **State Management**: Communicates with the [GameStateMachine](../architecture/state-machine.md) to transition control back to the [Main Menu State](main-menu.md).

## Related States

* [Main Menu State](main-menu.md)
* [Play State](play.md)