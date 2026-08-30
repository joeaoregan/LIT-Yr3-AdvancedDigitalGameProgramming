import { BaseState } from './BaseState.js';
import { stateNames, WIDTH, HEIGHT, HUD_HEIGHT, WORLD_HEIGHT } from '../config.js';
import { Player } from '../entities/Player.js';
import { Glider, AngryGlider, ShotGlider, Turret, RoofTurret, Level1Boss, PowerUp } from '../entities/Enemies.js';
import { TheTextureManager } from '../TextureManager.js';
import { TheSoundManager } from '../SoundManager.js';
import { LevelParser } from '../LevelParser.js';

export class PlayState extends BaseState {
  getStateID() {
    return stateNames.PLAY;
  }

  constructor() {
    super();
    this.player = null;
    this.enemies = [];
    this.pendingEnemies = [];
    this.tileLayers = [];
    this.spawnTimer = 0;
    this.bossSpawned = false;
    this.bgX = 0;
    this.scrollDistance = 0;
    this.bgSpeed = 1.8;
    this.levelParser = new LevelParser();
  }

  async enter() {
    this.player = new Player();
    this.enemies = [];
    this.pendingEnemies = [];
    this.tileLayers = [];
    this.spawnTimer = 0;
    this.bossSpawned = false;
    this.bgX = 0;
    this.scrollDistance = 0;
    this.game.bulletHandler.clearBullets();
    TheSoundManager.playMusic('music1');

    // Load Level 1 map definition from TMX
    const mapData = await this.levelParser.parseLevel('1-AlienAttack/Alien Attack K00203642/assets/map1.tmx');
    if (mapData) {
      if (mapData.tileLayers && mapData.tileLayers.length > 0) {
        this.tileLayers = mapData.tileLayers;
      }
      if (mapData.spawnedObjects && mapData.spawnedObjects.length > 0) {
        // Sort enemies by X coordinate for level scrolling activation
        this.pendingEnemies = mapData.spawnedObjects.sort((a, b) => a.mapX - b.mapX);
        this.hasMapBoss = this.pendingEnemies.some((e) => e.typeStr === 'Level1Boss');
      }
    }
  }

  exit() {
    TheSoundManager.stopMusic();
  }


  spawnRandomEnemy() {
    const y = 20 + Math.random() * (WORLD_HEIGHT - 110);
    const rand = Math.random();

    if (rand < 0.35) {
      this.enemies.push(new Glider(970, y));
    } else if (rand < 0.65) {
      this.enemies.push(new AngryGlider(970, y));
    } else if (rand < 0.85) {
      this.enemies.push(new ShotGlider(970, y));
    } else if (rand < 0.93) {
      const isRoof = Math.random() > 0.5;
      const turret = isRoof ? new RoofTurret(970, 4) : new Turret(970, WORLD_HEIGHT - 100);
      turret.mapX = this.scrollDistance + 970;
      this.enemies.push(turret);
    } else {
      this.enemies.push(new PowerUp(970, y));
    }
  }

  update(dt) {
    const input = this.game.input;

    if (input.isDown('escape') || input.isDown('p')) {
      this.game.pushState(stateNames.PAUSE);
      return;
    }

    // Horizontal level scroll progress
    this.scrollDistance += this.bgSpeed;
    this.bgX -= this.bgSpeed;
    if (this.bgX <= -960) {
      this.bgX = 0;
    }

    // Activate pending enemies from map when scroll reaches their map X position
    while (
      Array.isArray(this.pendingEnemies) &&
      this.pendingEnemies.length > 0 &&
      this.pendingEnemies[0].mapX <= this.scrollDistance + 960
    ) {
      const enemy = this.pendingEnemies.shift();
      enemy.position.x = enemy.mapX - this.scrollDistance;
      this.enemies.push(enemy);
    }


    if (this.player.bDead) {
      this.game.lives--;
      if (this.game.lives <= 0) {
        this.game.bestScore = Math.max(this.game.bestScore, this.game.score);
        this.game.changeState(stateNames.ENTER_NAME);
        return;
      } else {
        this.player.resurrect();
      }
    }

    this.player.update(dt, this.game);

    // Score-triggered boss is only a fallback for maps with no boss object, and never
    // at the start of a run so a carried-over score can't spawn it on the player
    if (!this.hasMapBoss && !this.bossSpawned && this.game.score >= 600 && this.scrollDistance > 960) {
      this.bossSpawned = true;
      this.enemies.push(new Level1Boss(750, 180));
    }

    // Fallback enemy spawner if map pending list is empty
    if (!this.bossSpawned && this.pendingEnemies.length === 0) {
      this.spawnTimer -= dt;
      if (this.spawnTimer <= 0) {
        this.spawnRandomEnemy();
        this.spawnTimer = Math.max(320, 850 - this.game.level * 45);
      }
    }

    this.game.bulletHandler.updateBullets(dt);

    for (let i = this.enemies.length - 1; i >= 0; i--) {
      const enemy = this.enemies[i];
      enemy.update(dt, this.game);

      // Keep map-anchored objects locked to their tile position as the level scrolls
      if (enemy.scrollsWithMap && typeof enemy.mapX === 'number') {
        enemy.position.x = enemy.mapX - this.scrollDistance;
      }

      if (enemy.bDead) {
        if (enemy.typeStr === 'Level1Boss') {
          this.game.score += 500;
          this.game.changeState(stateNames.LEVEL_COMPLETE);
          return;
        }
        this.enemies.splice(i, 1);
        continue;
      }

      if (enemy.position.x < -200 || enemy.position.x > 1200) {
        this.enemies.splice(i, 1);
      }
    }

    this.game.collisionManager.checkAll(this.player, this.enemies, this.game.bulletHandler, this.tileLayers, this.scrollDistance, this.game);


    if (this.game.score > 0 && this.game.score % 250 === 0) {
      this.game.level = Math.floor(this.game.score / 250) + 1;
    }
  }

  render(ctx) {
    ctx.fillStyle = '#071923';
    ctx.fillRect(0, 0, WIDTH, HEIGHT);

    // World is drawn in its own viewport under the HUD, so map row 0 is never hidden
    ctx.save();
    ctx.beginPath();
    ctx.rect(0, HUD_HEIGHT, WIDTH, WORLD_HEIGHT);
    ctx.clip();
    ctx.translate(0, HUD_HEIGHT);

    // Draw scrolling background clouds
    TheTextureManager.draw('clouds1', Math.floor(this.bgX), 0, WIDTH, WORLD_HEIGHT, ctx);
    TheTextureManager.draw('clouds1', Math.floor(this.bgX) + WIDTH, 0, WIDTH, WORLD_HEIGHT, ctx);

    // Draw TMX map tile layers
    if (this.tileLayers && this.tileLayers.length > 0) {
      this.tileLayers.forEach((layer) => layer.render(ctx, this.scrollDistance));
    }

    this.player.draw(ctx);
    this.enemies.forEach((enemy) => enemy.draw(ctx));
    this.game.bulletHandler.drawBullets(ctx);
    ctx.restore();

    this.game.hud.render(ctx, this.game);
  }

}



