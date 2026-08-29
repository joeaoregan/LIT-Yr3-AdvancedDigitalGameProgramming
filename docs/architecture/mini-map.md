# MiniMap Architecture

The `MiniMap` provides a scaled-down, real-time overview of the entire level layout, showing the relative positions of the player and active enemies within the Alien Attack project.

## Core Components

* [MiniMap.h](https://github.com/joeaoregan/LIT-Yr3-AdvancedDigitalGameProgramming/blob/master/1-AlienAttack/Alien%20Attack%20K00203642/MiniMap.h): The dedicated class files responsible for translating the world coordinates of active game objects into miniaturised screen coordinates for the radar display.

## Mapping Process

* **Coordinate Translation**: Instead of rendering full-sized textures, the minimap calculates a scale factor based on the total level dimensions versus the minimap's designated UI dimensions. It translates the true world X and Y coordinates of entities into these scaled UI coordinates.
* **Entity Representation**: It uses simplified graphics, such as coloured rectangles or small icons, to represent the player, enemies, and key level boundaries on the map overlay.

## Execution and Usage

During the gameplay loop, the `PlayState` provides the [MiniMap](mini-map.md) with the latest entity positions. The minimap is then rendered as an overlay on the screen, typically alongside the [HUD](hud.md), to make certain the player always has spatial awareness of incoming threats that are currently off-screen.