import { WIDTH, HEIGHT, stateNames, difficulties } from './config.js';
import { InputHandler } from './InputHandler.js';
import { StateMachine } from './StateMachine.js';
import { BulletHandler } from './BulletHandler.js';
import { CollisionManager } from './CollisionManager.js';
import { HUD } from './HUD.js';

import { TitleScreenState } from './states/TitleScreenState.js';
import { MainMenuState } from './states/MainMenuState.js';
import { SettingsState } from './states/SettingsState.js';
import { InstructionsState } from './states/InstructionsState.js';
import { HighScoreState } from './states/HighScoreState.js';
import { EnterNameState } from './states/EnterNameState.js';
import { LevelObjectiveState } from './states/LevelObjectiveState.js';
import { PlayState } from './states/PlayState.js';
import { PauseState } from './states/PauseState.js';
import { LevelCompleteState } from './states/LevelCompleteState.js';
import { GameOverState } from './states/GameOverState.js';

export class Game {
  constructor(canvas) {
    this.canvas = canvas;
    this.ctx = canvas.getContext('2d');

    this.input = new InputHandler();
    this.input.bind(canvas);

    this.stateMachine = new StateMachine(this);
    this.bulletHandler = new BulletHandler();
    this.collisionManager = new CollisionManager();
    this.hud = new HUD();

    this.score = 0;
    this.bestScore = 0;
    this.lives = 3;
    this.level = 1;
    this.playerName = 'PLAYER';
    this.difficulty = difficulties.NORMAL;
    this.lastTime = 0;

    this.highScores = [
      { name: 'JOE', score: 1250 },
      { name: 'ACE', score: 980 },
      { name: 'SAM', score: 750 },
      { name: 'MAX', score: 500 },
      { name: 'LEO', score: 320 }
    ];

    this.stateRegistry = {
      [stateNames.TITLE_SCREEN]: TitleScreenState,
      [stateNames.MAIN_MENU]: MainMenuState,
      [stateNames.SETTINGS]: SettingsState,
      [stateNames.INSTRUCTIONS]: InstructionsState,
      [stateNames.HIGH_SCORE]: HighScoreState,
      [stateNames.ENTER_NAME]: EnterNameState,
      [stateNames.LEVEL_OBJECTIVE]: LevelObjectiveState,
      [stateNames.PLAY]: PlayState,
      [stateNames.PAUSE]: PauseState,
      [stateNames.LEVEL_COMPLETE]: LevelCompleteState,
      [stateNames.GAME_OVER]: GameOverState
    };

    this.changeState(stateNames.TITLE_SCREEN);
  }

  changeState(name) {
    const StateClass = this.stateRegistry[name];
    if (StateClass) {
      this.stateMachine.changeState(new StateClass());
    }
  }

  pushState(name) {
    const StateClass = this.stateRegistry[name];
    if (StateClass) {
      this.stateMachine.pushState(new StateClass());
    }
  }

  popState() {
    this.stateMachine.popState();
  }

  resetRun() {
    this.score = 0;
    this.lives = 3;
    this.level = 1;
    this.bulletHandler.clearBullets();
  }

  addHighScore(name, score) {
    this.highScores.push({ name, score });
    this.highScores.sort((a, b) => b.score - a.score);
    if (this.highScores.length > 10) {
      this.highScores.pop();
    }
  }

  update(dt) {
    this.stateMachine.update(dt);
  }

  render() {
    this.ctx.clearRect(0, 0, WIDTH, HEIGHT);
    this.stateMachine.render(this.ctx);
  }

  loop(timestamp) {
    const delta = Math.min(32, timestamp - (this.lastTime || timestamp));
    this.lastTime = timestamp;

    this.update(delta);
    this.render();
    requestAnimationFrame((time) => this.loop(time));
  }

  start() {
    requestAnimationFrame((time) => this.loop(time));
  }
}

