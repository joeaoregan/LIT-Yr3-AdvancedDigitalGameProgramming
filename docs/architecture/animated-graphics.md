# AnimatedGraphic Architecture

The `AnimatedGraphic` class represents visual sprite animations that cycle through frames automatically within the Alien Attack project. Inheriting from the base [GameObject](../game-objects/index.md) class, it manages frame rates and visual sequences for both looping scenery and transient effects such as explosions.

## Core Components

* [AnimatedGraphic.h](https://github.com/joeaoregan/LIT-Yr3-AdvancedDigitalGameProgramming/blob/master/1-AlienAttack/Alien%20Attack%20K00203642/AnimatedGraphic.h) & [AnimatedGraphic.cpp](https://github.com/joeaoregan/LIT-Yr3-AdvancedDigitalGameProgramming/blob/master/1-AlienAttack/Alien%20Attack%20K00203642/AnimatedGraphic.cpp): The concrete class files that handle frame timing, animation speed, and sprite sheet texture coordinates.

## Key Responsibilities

* **Frame Timing and Cycling**: The `update()` method calculates when to advance to the next sprite frame based on an assigned animation speed. Instead of relying on external managers to manually switch frames, the object maintains its own current frame index.
* **Rendering**: The `draw()` method is used to calculate the source rectangle for the texture based on the active frame, rendering the current slice of the sprite sheet to the target screen coordinates.
* **Factory Registration**: The class registers a unique string identifier with the [GameObjectFactory](object-factory.md). This is used to make certain that animated decorative objects or effects can be instantiated dynamically from map files or during runtime events.
* **Transient Effects**: When used for one-off animations like destruction effects, the object can flag itself for deletion once the full animation cycle has completed.