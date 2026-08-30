export const WIDTH = 960;
export const HEIGHT = 540;
export const HUD_HEIGHT = 48;
// The original renders the tile world into an 800x480 viewport with the HUD outside it
export const WORLD_HEIGHT = HEIGHT - HUD_HEIGHT;
export const FPS = 60;

export const GAME_NAME = 'Alien Attack';

export const stateNames = {
  TITLE_SCREEN: 'title',
  MAIN_MENU: 'main-menu',
  SETTINGS: 'settings',
  INSTRUCTIONS: 'instructions',
  HIGH_SCORE: 'high-score',
  ENTER_NAME: 'enter-name',
  LEVEL_OBJECTIVE: 'level-objective',
  PLAY: 'play',
  PAUSE: 'pause',
  LEVEL_COMPLETE: 'level-complete',
  GAME_OVER: 'game-over'
};

export const difficulties = {
  EASY: 'EASY',
  NORMAL: 'NORMAL',
  HARD: 'HARD'
};

