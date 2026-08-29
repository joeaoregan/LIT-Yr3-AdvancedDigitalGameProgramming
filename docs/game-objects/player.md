# Player Object

The `Player` class represents the user-controlled entity within the Alien Attack project. Inheriting from the base [GameObject](index.md) class, it encompasses the specific logic required for player movement, animation, and combat actions.

## Core Components

* **`Player.h` & `Player.cpp`**: The concrete implementations defining the player's attributes, such as health, movement speed, and current visual state.

## Key Responsibilities

* **Input Processing**: During the `update()` cycle, the player queries the [InputHandler](../architecture/input-handler.md) to determine keyboard or gamepad states. Instead of raw event polling, it translates these abstracted inputs into velocity and directional changes.
* **Combat Actions**: When the firing input is detected, the player class calculates the appropriate spawn coordinates and requests the [BulletHandler](../architecture/bullet-handler.md) to create a new player projectile.
* **Animation and Rendering**: The `draw()` method makes certain the correct sprite frame is rendered based on the player's current action, such as flying straight, banking, or taking damage.
* **Health and Status**: Maintains internal counters for health and lives. The [CollisionManager](../architecture/collision-manager.md) updates these values when an enemy or enemy bullet strikes the player.