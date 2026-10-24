# Game States

![Alien Attack State Machine & Lifecycle](../images/svg/state_machine.svg)

The Alien Attack application lifecycle is governed by a stack-based finite state machine (`GameStateMachine`). Rather than using global variables or conditional switch blocks, each screen and gameplay phase is implemented as an isolated `GameState` object with distinct initialisation, frame update, rendering, and teardown routines.

!!! tip "State Stack Design"  
    * **Non-Destructive Overlays**: Using `pushState()`, temporary screens like `PauseState` or `SettingsState` are pushed on top of `PlayState`. The underlying gameplay world remains in memory without ticking until the overlay is popped.
    * **State Resumption**: When an overlay exits via `popState()`, the state machine automatically triggers `resume()` on the newly uncovered state underneath.
    * **Clean Transitions**: Permanent scene switches (such as transitioning from `MainMenuState` to `PlayState` or upon game over) use `changeState()`, safely calling `onExit()` to release textures before instantiating the new scene.

---

## State Categories

### Menu & Configuration States
Interactive front-end states for game launch, customization, and player records:

* **[Main Menu](main-menu.md)**  
  The central hub providing options to launch gameplay, view high scores, adjust settings, or quit.
* **[Settings](settings.md)**  
  Configuration panel for sound effect volumes, background music, and controls.
* **[Instructions](instructions.md)**  
  Visual guide outlining keyboard controls, gamepad mappings, and primary objectives.
* **[High Score](high-score.md)**  
  Displays the persistent top-ten score table loaded from disk.
* **[Enter Name](enter-name.md)**  
  Interactive alphanumeric entry screen triggered when a player achieves a high score ranking.
* **[Level Objective](level-objective.md)**  
  Pre-flight briefing displayed before stage launch highlighting mission requirements.

### Gameplay & Lifecycle States
States managing live action, pausing, and terminal outcomes:

* **[Play](play.md)**  
  The core gameplay loop managing level tiles, player kinematics, hostile waves, and collisions.
* **[Pause](pause.md)**  
  Overlay state paused on top of `PlayState` allowing players to resume or return to the menu.
* **[Level Complete](level-complete.md)**  
  Victory screen presented upon defeating the stage boss, tallying bonus points before stage progression.
* **[Game Over](game-over.md)**  
  Defeat screen presented when player lives are exhausted, displaying final score and retry options.
