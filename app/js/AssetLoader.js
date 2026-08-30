import { TheTextureManager } from './TextureManager.js';
import { TheSoundManager } from './SoundManager.js';

const ASSET_BASE = '1-AlienAttack/Alien Attack K00203642/assets/';
const SFX_BASE = '1-AlienAttack/Alien Attack K00203642/SoundFX/';
const MUSIC_BASE = '1-AlienAttack/Alien Attack K00203642/OriginalMusic/';

// `frame` is the source cell size of a sprite sheet; omit it for single-frame images.
export const textureManifest = {
  // Player & Entities
  player: { src: `${ASSET_BASE}heli.png`, frame: [101, 43] },
  glider: { src: `${ASSET_BASE}enemy1.png`, frame: [38, 34] },
  enemy1: { src: `${ASSET_BASE}enemy1.png`, frame: [38, 34] },
  enemy2: { src: `${ASSET_BASE}enemy2.png`, frame: [38, 36] },
  enemy3: { src: `${ASSET_BASE}enemy3.png`, frame: [34, 35] },
  enemy4: { src: `${ASSET_BASE}enemy4.png`, frame: [38, 36] },
  angryenemy: { src: `${ASSET_BASE}angryenemy.png`, frame: [38, 36] },
  turret: { src: `${ASSET_BASE}turret.png`, frame: [52, 56] },
  boss: { src: `${ASSET_BASE}boss1.png`, frame: [183, 230] },
  squasher: { src: `${ASSET_BASE}squasher.png`, frame: [64, 128] },
  pounder: { src: `${ASSET_BASE}pounder.png`, frame: [64, 128] },
  powerUpID: { src: `${ASSET_BASE}PowerUpLife.png`, frame: [50, 20] },

  // Tilemaps & Backgrounds
  blocks1: { src: `${ASSET_BASE}blocks1.png` },
  blocks2: { src: `${ASSET_BASE}blocks2.png` },
  blocks3: { src: `${ASSET_BASE}blocks3.png` },
  land: { src: `${ASSET_BASE}land.png` },
  clouds1: { src: `${ASSET_BASE}clouds1.png` },
  clouds2: { src: `${ASSET_BASE}clouds2.png` },
  clouds: { src: `${ASSET_BASE}clouds.png` },
  grass: { src: `${ASSET_BASE}grass.png` },
  lives: { src: `${ASSET_BASE}lives.png`, frame: [32, 30] },
  minimap: { src: `${ASSET_BASE}minimap.png` },

  // Bullets & FX
  bullet1: { src: `${ASSET_BASE}bullet1.png` },
  bullet2: { src: `${ASSET_BASE}bullet2.png` },
  bullet3: { src: `${ASSET_BASE}bullet3.png` },
  bullet4: { src: `${ASSET_BASE}bullet4.png` },
  explosion: { src: `${ASSET_BASE}explosion.png`, frame: [40, 40] },
  largeexplosion: { src: `${ASSET_BASE}largeexplosion.png`, frame: [60, 60] },
  bossexplosion: { src: `${ASSET_BASE}bossexplosion.png`, frame: [180, 180] },

  // Menu assets
  attacklogo: { src: `${ASSET_BASE}AlienAttack.png`, frame: [360, 75] },
  playbutton: { src: `${ASSET_BASE}menuButtonPlay.png`, frame: [400, 100] },
  scorebutton: { src: `${ASSET_BASE}menuButtonScore.png`, frame: [400, 100] },
  settingsbutton: { src: `${ASSET_BASE}menuButtonSettings.png`, frame: [400, 100] },
  instructionsbutton: { src: `${ASSET_BASE}menuButtonInstructions.png`, frame: [400, 100] },
  exitbutton: { src: `${ASSET_BASE}menuButtonExit.png`, frame: [400, 100] },
  mainbutton: { src: `${ASSET_BASE}main.png`, frame: [200, 80] },
  restartbutton: { src: `${ASSET_BASE}restart.png`, frame: [200, 80] },
  resumebutton: { src: `${ASSET_BASE}resume.png`, frame: [200, 80] },
  titlebg: { src: `${ASSET_BASE}titles.png`, frame: [800, 640] },
  anykey: { src: `${ASSET_BASE}anykey.png`, frame: [540, 50] },
  gameovertext: { src: `${ASSET_BASE}gameover.png`, frame: [380, 30] }
};


export async function preloadAllAssets() {
  const promises = [];
  for (const [id, entry] of Object.entries(textureManifest)) {
    const spec = entry.frame ? { frameWidth: entry.frame[0], frameHeight: entry.frame[1] } : null;
    promises.push(TheTextureManager.load(id, entry.src, spec));
  }

  // Preload sound effects & music tracks
  TheSoundManager.loadSound('phaser', `${ASSET_BASE}phaser.wav`);
  TheSoundManager.loadSound('boom', `${ASSET_BASE}boom.wav`);
  TheSoundManager.loadSound('powerup', `${SFX_BASE}powerup.wav`);
  TheSoundManager.loadSound('laser2', `${SFX_BASE}laser2.wav`);
  TheSoundManager.loadSound('blast', `${SFX_BASE}blast.wav`);
  TheSoundManager.loadSound('button', `${SFX_BASE}button1.wav`);

  // Original soundtrack shipped with the C++ build, plus the stock SDL-book track
  TheSoundManager.loadMusic('music1', `${MUSIC_BASE}song1.mp3`);
  TheSoundManager.loadMusic('music2', `${MUSIC_BASE}song2.mp3`);
  TheSoundManager.loadMusic('music3', `${ASSET_BASE}DST_ElectroRock.ogg`);

  await Promise.all(promises);
}

