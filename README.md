# Advanced Digital Game Programming

![LIT](https://img.shields.io/badge/Limerick%20Institute%20of%20Technology-2017-red?style=flat-square&logo=data:image/svg+xml;base64,PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0iVVRGLTgiIHN0YW5kYWxvbmU9Im5vIj8+CjwhLS0gQ3JlYXRlZCB3aXRoIElua3NjYXBlIChodHRwOi8vd3d3Lmlua3NjYXBlLm9yZy8pIC0tPgoKPHN2ZwogICB3aWR0aD0iNTYuMzI5OTQ4bW0iCiAgIGhlaWdodD0iNTYuODY3NzgzbW0iCiAgIHZpZXdCb3g9IjAgMCA1Ni4zMjk5NDggNTYuODY3NzgzIgogICB2ZXJzaW9uPSIxLjEiCiAgIGlkPSJzdmcxIgogICB4bWw6c3BhY2U9InByZXNlcnZlIgogICB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciCiAgIHhtbG5zOnN2Zz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciPjxkZWZzCiAgICAgaWQ9ImRlZnMxIiAvPjxnCiAgICAgaWQ9ImxheWVyMSIKICAgICB0cmFuc2Zvcm09InRyYW5zbGF0ZSgtMTAwLjgwNjE2LC0xMTEuMDAxNTMpIj48cGF0aAogICAgICAgZD0ibSAxMjMuMzIyMzgsMTExLjYxNTU4IGMgMy43MDQxNiwtMC43NjcyOSA3LjUxNDE2LC0wLjgyMDIxIDExLjI0NDc5LC0wLjEzMjI5IGwgLTIuMzU0NzksMTIuNDYxODcgYyAtMC45NTI1LC0wLjE4NTIgLTEuOTMxNDYsLTAuMjY0NTggLTIuOTEwNDIsLTAuMjY0NTggLTUuNzY3OTIsMCAtMTEuMDU5NTgsMy4xMjIwOCAtMTMuODM3NzEsOC4xNDkxNyBsIC00LjE4MDQyLC0yLjI3NTQyIGMgMi44ODM5NiwtNS4yMTIyOSA3Ljg1ODEzLC04LjkxNjQ2IDEzLjcwNTQyLC0xMC4xODY0NiB6IG0gNi42OTM5NSwyMi4xNzIwOCBjIC0wLjIzODEyLC0wLjAyNjQgLTAuNDc2MjUsLTAuMDUyOSAtMC43MTQzNywtMC4wNTI5IC0xLjY0MDQyLDAgLTMuMjAxNDYsMC43MTQzNyAtNC4yNTk3OSwxLjkzMTQ2IGwgLTIuNjk4NzUsLTIuMzU0OCBjIDEuNzcyNzEsLTIuMDEwODMgNC4zMTI3MSwtMy4xNDg1NCA2Ljk4NSwtMy4xNDg1NCAwLjM3MDQxLDAgMC43NjcyOSwwLjAyNjUgMS4xMzc3MSwwLjA3OTQgeiBtIDE5LjU1MjcxLDI1LjYzODEzIGMgLTYuNjY3NSw2LjcyMDQyIC0xNi4yMTg5Niw5LjY4Mzc1IC0yNS41MzIyOSw3Ljk2Mzk2IGwgMS40ODE2NywtNy43Nzg3NSBjIDYuNzIwNDEsMS4yNDM1NCAxMy41OTk1OCwtMC44OTk1OSAxOC40MTUsLTUuNzQxNDYgeiBtIC0xMy42Nzg5NiwtMTMuNDkzNzUgNC42MzAyMSw0LjU1MDgzIGMgLTMuNjc3NzEsMy43MzA2MyAtOC45OTU4Myw1LjM3MTA0IC0xNC4xNTUyMSw0LjQxODU0IGwgMS4xOTA2MywtNi4zNzY0NSBjIDAuNTU1NjIsMC4xMDU4MyAxLjEzNzcxLDAuMTU4NzUgMS43MTk3OSwwLjE1ODc1IDIuNTEzNTQsMCA0Ljg2ODMzLC0wLjk3ODk2IDYuNjE0NTgsLTIuNzUxNjcgeiBtIC0xNy42NDc3LDQuNzA5NTggYyAxLjAwNTQxLDEuMDA1NDIgMi4xNDMxMiwxLjg1MjA5IDMuMzg2NjYsMi41NCBsIC0yLjMyODMzLDQuMTUzOTYgYyAtMS42MTM5NiwtMC44OTk1OCAtMy4wOTU2MywtMi4wMTA4MyAtNC40MTg1NCwtMy4zMDcyOSBsIC01LjU4MjcxLDUuNjM1NjIgYyAtNS40NTA0MiwtNS4zMTgxMiAtOC41MTk1OCwtMTIuNjIwNjIgLTguNDkzMTMsLTIwLjI0MDYyIDAsLTEuNzk5MTcgMC4xNTg3NSwtMy41OTgzMyAwLjUwMjcxLC01LjM3MTA0IGwgNy44MDUyMSwxLjUwODEyIGMgLTAuMjM4MTIsMS4yNyAtMC4zNzA0MiwyLjU2NjQ2IC0wLjM3MDQyLDMuODYyOTIgMCwyLjQwNzcxIDAuNDIzMzQsNC43ODg5NiAxLjI0MzU1LDcuMDY0MzcgbCA0LjQ3MTQ1LC0xLjY0MDQxIGMgLTAuOTc4OTUsLTIuNjcyMjkgLTEuMjE3MDgsLTUuNTgyNzEgLTAuNjg3OTEsLTguMzg3MjkgbCA2LjM3NjQ2LDEuMjQzNTQgYyAtMC4xMDU4NCwwLjU4MjA4IC0wLjE1ODc1LDEuMTY0MTYgLTAuMTU4NzUsMS43NDYyNSAwLDIuNDg3MDggMS4wMDU0MSw0Ljg2ODMzIDIuNzc4MTIsNi41ODgxMiB6IG0gMjQuNTc5NzksLTI2LjY0MzU0IDYuNTA4NzUsMTAuOTI3MjkgYyAwLjU1NTYyLDIuNDA3NzEgMC42NjE0NSw0LjkyMTI1IDAuMzE3NSw3LjM1NTQyIEwgMTM4LjQ4MywxNDAuNzE5NzUgYyAtMC4xMzIyOSwwLjk3ODk2IC0wLjQyMzMzLDEuOTA1IC0wLjg0NjY3LDIuODA0NTggbCAtMy4yNTQzNywtMS41NjEwNCBjIDEuMTM3NzEsLTIuMzAxODggMC42MDg1NCwtNS4xMDY0NiAtMS4zNDkzOCwtNi43OTk3OSBsIDIuMzU0OCwtMi42OTg3NSBjIDEuNDgxNjYsMS4yOTY0NiAyLjUxMzU0LDMuMDE2MjUgMi45MzY4Nyw0LjkyMTI1IGwgNi4zNSwtMS40Mjg3NSBjIC0wLjc0MDgzLC0zLjI1NDM4IC0yLjQ4NzA4LC02LjE5MTI1IC01LjAwMDYzLC04LjM4NzI5IHogbSA2LjUzNTIsMTAuOTAwODMgLTYuNTA4NzUsLTEwLjkyNzI5IGMgLTEuMzc1ODMsLTEuMjE3MDggLTIuOTEwNDEsLTIuMjIyNSAtNC41NTA4MywtMy4wMTYyNSBsIDMuNDY2MDQsLTcuMTQzNzUgYyA3LjgwNTIxLDMuNzgzNTQgMTMuNDY3MjksMTAuOTAwODQgMTUuMzcyMjksMTkuMzQxMDQgeiIKICAgICAgIHN0eWxlPSJmaWxsOiNkNzFkMWU7c3Ryb2tlLXdpZHRoOjAuMjY0NTgzIgogICAgICAgaWQ9InBhdGgxLTgiIC8+PC9nPjxzdHlsZQogICAgIHR5cGU9InRleHQvY3NzIgogICAgIGlkPSJzdHlsZTEiPgoJLnN0MHtmaWxsOiNENzFEMUU7fQo8L3N0eWxlPjwvc3ZnPgo=)
![Advanced Digital Game Programming](https://img.shields.io/badge/Module-Advanced%20Digital%20Game%20Programming-blue?style=flat-square)
![Design Patterns](https://img.shields.io/badge/Topic-Design%20Patterns-gold?style=flat-square)

![C++](https://img.shields.io/badge/C%2B%2B-MSVC%20v140-00599C?style=flat-square)
![SDL2](https://img.shields.io/badge/SDL-2.0.5-000000?style=flat-square)
![SDL_mixer](https://img.shields.io/badge/SDL_mixer-2.0.1-000000?style=flat-square)
![SDL_image](https://img.shields.io/badge/SDL_image-2.0.5-000000?style=flat-square)
![SDL_ttf](https://img.shields.io/badge/SDL_ttf-2.0.5-000000?style=flat-square)
![Code::Blocks](https://img.shields.io/badge/Code::Blocks-IDE-1C93C1?style=flat-square)
![Tiled](https://img.shields.io/badge/Tiled-Map%20Editor-3D7E9C?style=flat-square)

![GitHub repo size](https://img.shields.io/github/repo-size/joeaoregan/LIT-Yr3-AdvancedDigitalGameProgramming?style=flat-square\&color=orange)
![Last Commit](https://img.shields.io/github/last-commit/joeaoregan/LIT-Yr3-AdvancedDigitalGameProgramming?style=flat-square\&color=blue)
![GitHub top language](https://img.shields.io/github/languages/top/joeaoregan/LIT-Yr3-AdvancedDigitalGameProgramming)
![Stars](https://img.shields.io/github/stars/joeaoregan/LIT-Yr3-AdvancedDigitalGameProgramming?style=social)

## Limerick Institute of Technology
### Year 3 (2016/17), Semester 6

**Student Name**: Joe O'Regan  
**Student Number**: K00203642  
**Course**: BSc (Honours) in Computing (Games Design and Development)  
**Module**: Advanced Digital Game Programming

---

## Alien Attack

[Play the Game Online](https://joeaoregan.github.io/LIT-Yr3-AdvancedDigitalGameProgramming/play/)

Continuous Assessment game for Advanced Digital Game Programming Module of Year 3.
Modified Alien Attack game from [SDL Game Development by Shaun Mitchell](https://www.packtpub.com/game-development/sdl-game-development). 

Using helpful SDL 2.0 tutorials from [Lazy Foo' Productions](http://lazyfoo.net/tutorials/SDL/index.php) for inspiration :smile: :grinning:

> [!NOTE]
> 10/09/2017 Started Editing Code To Work With Code::Blocks IDE.

**Features:**
* Design Patterns (Factory Method, Singleton)
* Object-Oriented Programming
* Inheritance


## Screenshots:

<details closed>
<summary>
<div style="height: 90px; overflow: hidden;">
<img src="https://raw.githubusercontent.com/joeaoregan/LIT-Yr3-S6-AdvancedDigitalGameDesign/master/Screenshots/AlienAttack1Menu.jpg" style="height: 90px; width: auto; object-fit: cover;"/>
<img src="https://raw.githubusercontent.com/joeaoregan/LIT-Yr3-S6-AdvancedDigitalGameDesign/master/Screenshots/AlienAttack2HighScores.png" style="height: 90px; width: auto; object-fit: cover;"/>
<img src="https://raw.githubusercontent.com/joeaoregan/LIT-Yr3-S6-AdvancedDigitalGameDesign/master/Screenshots/AlienAttack3Settings.png" style="height: 90px; width: auto; object-fit: cover;"/>
<img src="https://raw.githubusercontent.com/joeaoregan/LIT-Yr3-S6-AdvancedDigitalGameDesign/master/Screenshots/AlienAttack4Instructions.jpg" style="height: 90px; width: auto; object-fit: cover;"/>
<img src="https://raw.githubusercontent.com/joeaoregan/LIT-Yr3-S6-AdvancedDigitalGameDesign/master/Screenshots/AlienAttack5EnterName.png" style="height: 90px; width: auto; object-fit: cover;"/>
<img src="https://raw.githubusercontent.com/joeaoregan/LIT-Yr3-S6-AdvancedDigitalGameDesign/master/Screenshots/AlienAttack6ObjectiveL1.png" style="height: 90px; width: auto; object-fit: cover;"/>
<img src="https://raw.githubusercontent.com/joeaoregan/LIT-Yr3-S6-AdvancedDigitalGameDesign/master/Screenshots/AlienAttack7StartLevel1.jpg" style="height: 90px; width: auto; object-fit: cover;"/>
<img src="https://raw.githubusercontent.com/joeaoregan/LIT-Yr3-S6-AdvancedDigitalGameDesign/master/Screenshots/AlienAttack8KeepOffTheGrass1.jpg" style="height: 90px; width: auto; object-fit: cover;"/>
<img src="https://raw.githubusercontent.com/joeaoregan/LIT-Yr3-S6-AdvancedDigitalGameDesign/master/Screenshots/AlienAttack9KeepOffTheGrass2.jpg" style="height: 90px; width: auto; object-fit: cover;"/>
<img src="https://raw.githubusercontent.com/joeaoregan/LIT-Yr3-S6-AdvancedDigitalGameDesign/master/Screenshots/AlienAttack10Pounder.jpg" style="height: 90px; width: auto; object-fit: cover;"/>
<img src="https://raw.githubusercontent.com/joeaoregan/LIT-Yr3-S6-AdvancedDigitalGameDesign/master/Screenshots/AlienAttack11Pause.jpg" style="height: 90px; width: auto; object-fit: cover;"/>
<img src="https://raw.githubusercontent.com/joeaoregan/LIT-Yr3-S6-AdvancedDigitalGameDesign/master/Screenshots/AlienAttack12EOLBoss.jpg" style="height: 90px; width: auto; object-fit: cover;"/>
<img src="https://raw.githubusercontent.com/joeaoregan/LIT-Yr3-S6-AdvancedDigitalGameDesign/master/Screenshots/AlienAttack13Level2.jpg" style="height: 90px; width: auto; object-fit: cover;"/>
<img src="https://raw.githubusercontent.com/joeaoregan/LIT-Yr3-S6-AdvancedDigitalGameDesign/master/Screenshots/AlienAttack14GameOver.jpg " style="height: 90px; width: auto; object-fit: cover;"/>
</div>
<p>Click here for larger images.</p>
</summary>

<img src="https://raw.githubusercontent.com/joeaoregan/LIT-Yr3-S6-AdvancedDigitalGameDesign/master/Screenshots/AlienAttack1Menu.jpg" title="Alien Attack: Menu"/>
<h6>The game begins at the main menu.</h6>
<img src="https://raw.githubusercontent.com/joeaoregan/LIT-Yr3-S6-AdvancedDigitalGameDesign/master/Screenshots/AlienAttack2HighScores.png" title="Alien Attack: High Scores Menu"/>
<h6>High Scores table has been implemented using text files to save the player name and scores.</h6>
<img src="https://raw.githubusercontent.com/joeaoregan/LIT-Yr3-S6-AdvancedDigitalGameDesign/master/Screenshots/AlienAttack3Settings.png" title="Alien Attack: Settings Menu"/>
<h6>Game settings such as full screen/windowed, audio volumes, and game difficulty can be adjusted in the settings menu.</h6>
<img src="https://raw.githubusercontent.com/joeaoregan/LIT-Yr3-S6-AdvancedDigitalGameDesign/master/Screenshots/AlienAttack4Instructions.jpg" title="Alien Attack: Instructions Menu"/>
<h6>The instructions menu displays the controls for gamepad and keyboard.</h6>
<img src="https://raw.githubusercontent.com/joeaoregan/LIT-Yr3-S6-AdvancedDigitalGameDesign/master/Screenshots/AlienAttack5EnterName.png" title="Alien Attack: Enter Name State"/>
<h6>Before progressing to the level the Enter Name State is used to enter the players name, used to save scores at the end of the game.</h6>
<img src="https://raw.githubusercontent.com/joeaoregan/LIT-Yr3-S6-AdvancedDigitalGameDesign/master/Screenshots/AlienAttack6ObjectiveL1.png" title="Alien Attack: Level Objectives"/>
<h6>Objectives are displayed at the start of each level, and must be completed to progress to the following levels.</h6>
<img src="https://raw.githubusercontent.com/joeaoregan/LIT-Yr3-S6-AdvancedDigitalGameDesign/master/Screenshots/AlienAttack7StartLevel1.jpg" title="Alien Attack: Level 1 Start"/>
<h6>The player must avoid obstacles, and destroy enemies. A map on the HUD displays the players progress.</h6>
<img src="https://raw.githubusercontent.com/joeaoregan/LIT-Yr3-S6-AdvancedDigitalGameDesign/master/Screenshots/AlienAttack8KeepOffTheGrass1.jpg" title="Alien Attack: Flying Low"/>
<h6>The player is warned when flying to low to the ground.</h6>
<img src="https://raw.githubusercontent.com/joeaoregan/LIT-Yr3-S6-AdvancedDigitalGameDesign/master/Screenshots/AlienAttack9KeepOffTheGrass2.jpg" title="Alien Attack: Collisions"/>
<h6>If the player collides with objects on the collision layer they are destroyed.</h6>
<img src="https://raw.githubusercontent.com/joeaoregan/LIT-Yr3-S6-AdvancedDigitalGameDesign/master/Screenshots/AlienAttack10Pounder.jpg" title="Alien Attack: Obstacles"/>
<h6>Some of the obstacles move, to make it more difficult for the player. Lowering the difficulty in settings decreases the moving obstacles.</h6>
<img src="https://raw.githubusercontent.com/joeaoregan/LIT-Yr3-S6-AdvancedDigitalGameDesign/master/Screenshots/AlienAttack11Pause.jpg" title="Attack: Pause"/>
<h6>Pressing "Esc" brings the player to the Pause State, where they can return to the main menu, or resume the game later.</h6>
<img src="https://raw.githubusercontent.com/joeaoregan/LIT-Yr3-S6-AdvancedDigitalGameDesign/master/Screenshots/AlienAttack12EOLBoss.jpg" title="Alien Attack: End of Level Boss"/>
<h6>The player must destroy the end-of-level boss to progress to the next level. A health bar indicates the health of the boss enemy.</h6>
<img src="https://raw.githubusercontent.com/joeaoregan/LIT-Yr3-S6-AdvancedDigitalGameDesign/master/Screenshots/AlienAttack13Level2.jpg" title="Alien Attack: Level 2"/>
<h6>Level 2 uses a different tiled layout and background, with more enemies to deal with. Level 3 is also along the same lines.</h6>
<img src="https://raw.githubusercontent.com/joeaoregan/LIT-Yr3-S6-AdvancedDigitalGameDesign/master/Screenshots/AlienAttack14GameOver.jpg" title="Alien Attack: Game Over"/>
<h6>When the game is over the score is displayed, and the player can choose to restart the game, or return to the main menu.</h6>

</details>

---

## Links and References:

#### Game Trailer:
[![Game Trailer](https://raw.githubusercontent.com/joeaoregan/LIT-Yr3-S6-AdvancedDigitalGameDesign/master/Screenshots/YouTube.jpg)](https://youtu.be/JNEkne0aIOY)
###### YouTube: Trailer

> [!NOTE]
> YouTube Trailer Created as part of Assignment Spec.

[Lazy Foo' Productions](http://lazyfoo.net/tutorials/SDL/index.php)

[SDL Game Development, Shaun Mitchell](https://www.packtpub.com/game-development/sdl-game-development)

[Tiled Map Editor](https://www.mapeditor.org/)