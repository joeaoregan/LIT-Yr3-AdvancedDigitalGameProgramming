# InputHandler Architecture

The `InputHandler` manages user input from the keyboard, mouse, and game controllers for the Alien Attack project. It operates as a singleton to provide global, unified access to input states across all active game states and entities.

## Core Components

* [InputHandler.h](https://github.com/joeaoregan/LIT-Yr3-AdvancedDigitalGameProgramming/blob/master/1-AlienAttack/Alien%20Attack%20K00203642/InputHandler.h) & [InputHandler.cpp](https://github.com/joeaoregan/LIT-Yr3-AdvancedDigitalGameProgramming/blob/master/1-AlienAttack/Alien%20Attack%20K00203642/InputHandler.cpp): The central manager class responsible for polling SDL hardware events and storing the current state of all supported input devices.

## Input Processing

* **Event Polling**: The handler loops through `SDL_PollEvent` during the main game loop to capture hardware interrupts, updating its internal state arrays before game objects process their logic.
* **Keyboard State**: Maintains a reference to the current keyboard state array, allowing entities to seamlessly check if specific keys are held down.
* **Mouse & Joystick Management**: Tracks mouse cursor coordinates, mouse button clicks, and gamepad axis or button states, exposing them through simple getter functions.

## Execution and Usage

During the active phase, entities like the [Player](../game-objects/player.md) query the `InputHandler` within their `update()` methods to dictate movement and actions. Instead of placing raw SDL event processing directly into individual entity classes, the `InputHandler` abstracts this complexity. This centralised approach makes certain that input logic remains clean, decoupled, and easy to maintain across the entire project.