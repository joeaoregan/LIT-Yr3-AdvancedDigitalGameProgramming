# LevelParser Architecture

The `LevelParser` translates external map data files into a playable `Level` object within the Alien Attack game. Instead of hardcoding level layouts directly in C++, this architecture allows you to design stages using external map editors (such as Tiled) and load them dynamically at runtime.

## Core Components

* [LevelParser.h](https://github.com/joeaoregan/LIT-Yr3-AdvancedDigitalGameProgramming/blob/master/1-AlienAttack/Alien%20Attack%20K00203642/LevelParser.h) & [LevelParser.cpp](https://github.com/joeaoregan/LIT-Yr3-AdvancedDigitalGameProgramming/blob/master/1-AlienAttack/Alien%20Attack%20K00203642/LevelParser.cpp): The primary parser that reads and decodes the level data (typically in XML or JSON format). It extracts tilesets, collision boundaries, and entity data to construct the level.
* [Level.h](https://github.com/joeaoregan/LIT-Yr3-AdvancedDigitalGameProgramming/blob/master/1-AlienAttack/Alien%20Attack%20K00203642/Level.h) & [Level.cpp](https://github.com/joeaoregan/LIT-Yr3-AdvancedDigitalGameProgramming/blob/master/1-AlienAttack/Alien%20Attack%20K00203642/Level.cpp): Represents the fully parsed and assembled level in memory. It holds a collection of `Layer` pointers and manages their sequential update and render cycles.
* [Layer.h](https://github.com/joeaoregan/LIT-Yr3-AdvancedDigitalGameProgramming/blob/master/1-AlienAttack/Alien%20Attack%20K00203642/Layer.h): An abstract base class defining the standard interface for any map layer, guaranteeing that all layers can be updated and rendered uniformly.
* [ObjectLayer.h](https://github.com/joeaoregan/LIT-Yr3-AdvancedDigitalGameProgramming/blob/master/1-AlienAttack/Alien%20Attack%20K00203642/ObjectLayer.h) & [ObjectLayer.cpp](https://github.com/joeaoregan/LIT-Yr3-AdvancedDigitalGameProgramming/blob/master/1-AlienAttack/Alien%20Attack%20K00203642/ObjectLayer.cpp): A concrete implementation of a layer used specifically to manage dynamic entities. When the parser reads an object layer, it extracts the string IDs and coordinates, passing them to the [GameObjectFactory](object-factory.md) to instantiate enemies, the player, or power-ups.

## Parsing Process

1. **Initialization:** The parser receives a file path, opens the map file, and creates a new `Level` instance.
2. **Tileset Extraction:** It reads tileset properties and image source paths to make certain the correct textures are loaded into memory and are ready for rendering.
3. **Layer Construction:** It iterates through the map data, building the background, collision, and foreground layers. 
4. **Entity Spawning:** For interactive object layers, the parser extracts the specific attributes of each entity (e.g., x/y coordinates, type, width, height) and uses the [GameObjectFactory](object-factory.md) to spawn them into the level.