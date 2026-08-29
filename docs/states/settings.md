# Settings State

The `SettingsState` class represents the configuration and options interface within the Alien Attack project. Inheriting from the base [GameState](game.md) class, it provides a menu where the player can adjust preferences such as audio levels, controls, or graphical options.

## Core Components

* [SettingsState.h](https://github.com/joeaoregan/LIT-Yr3-AdvancedDigitalGameProgramming/blob/master/1-AlienAttack/Alien%20Attack%20K00203642/SettingsState.h) & [SettingsState.cpp](https://github.com/joeaoregan/LIT-Yr3-AdvancedDigitalGameProgramming/blob/master/1-AlienAttack/Alien%20Attack%20K00203642/SettingsState.cpp): The concrete implementation files that define the layout and behavior of the settings screen.

## Key Responsibilities

* **User Interaction**: Coordinates with the [InputHandler](../architecture/input-handler.md) to detect mouse clicks or keyboard inputs on configuration sliders and buttons.
* **State Management**: Communicates with the [GameStateMachine](../architecture/state-machine.md) to return control back to the [Main Menu State](main-menu.md) or the [Pause State](pause.md) once configurations are saved or cancelled.
* **Lifecycle Handling**: Manages loading and unloading of configuration assets via `onEnter()` and `onExit()` methods when toggling the settings view.

## Related States

* [Main Menu State](main-menu.md)
* [Pause State](pause.md)