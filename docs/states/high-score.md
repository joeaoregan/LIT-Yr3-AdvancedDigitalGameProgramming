# High Score State

The `HighScoreState` class represents the leaderboard interface within the Alien Attack project. Inheriting from the base [GameState](game.md) class, it manages the retrieval, formatting, and display of top player scores achieved during gameplay.

## Core Components

* [HighScoreState.h](https://github.com/joeaoregan/LIT-Yr3-AdvancedDigitalGameProgramming/blob/master/1-AlienAttack/Alien%20Attack%20K00203642/HighScoreState.h) & [HighScoreState.cpp](https://github.com/joeaoregan/LIT-Yr3-AdvancedDigitalGameProgramming/blob/master/1-AlienAttack/Alien%20Attack%20K00203642/HighScoreState.cpp): The concrete implementation files that define the layout and behavior of the high score display screen.

## Key Responsibilities

* **Leaderboard Rendering**: Manages the graphical presentation of ranked scores, interfacing with text rendering elements to show player achievements clearly.
* **Navigation Control**: Coordinates with the [InputHandler](../architecture/input-handler.md) to detect user inputs, allowing players to dismiss the screen and return to the main menu.
* **State Management**: Communicates with the [GameStateMachine](../architecture/state-machine.md) to facilitate smooth transitions back to the [Main Menu State](main-menu.md).

## Related States

* [Main Menu State](main-menu.md)
* [Play State](play.md)