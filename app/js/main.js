import { WIDTH, HEIGHT } from './config.js';
import { Game } from './Game.js';
import { preloadAllAssets } from './AssetLoader.js';

const canvas = document.getElementById('game');
canvas.width = WIDTH;
canvas.height = HEIGHT;

const game = new Game(canvas);
window.__alienAttackGame = game;

preloadAllAssets().then(() => {
  game.start();
});

