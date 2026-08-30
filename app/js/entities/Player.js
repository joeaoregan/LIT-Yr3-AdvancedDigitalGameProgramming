import { ShooterObject } from '../GameObject.js';
import { Vector2D } from '../Vector2D.js';
import { WIDTH, WORLD_HEIGHT } from '../config.js';
import { TheTextureManager } from '../TextureManager.js';
import { TheSoundManager } from '../SoundManager.js';
import { COLLISION_BULLET, COLLISION_POWERUP } from './PlayerConsts.js';

export class Player extends ShooterObject {
  constructor() {
    super();
    this.typeStr = 'Player';
    this.textureID = 'player';
    this.width = 101;
    this.height = 43;
    this.position = new Vector2D(80, WORLD_HEIGHT / 2 - 23);
    this.moveSpeed = 4.5;
    this.bulletFiringSpeed = 150;
    this.bulletCounter = 0;
    this.secondaryCounter = 0;
    this.invulnerable = false;
    this.invulnerableTime = 2000;
    this.invulnerableCounter = 0;
    this.health = 100;
    this.maxHealth = 100;

    this.numFrames = 5;
    this.currentFrame = 0;
    this.frameTimer = 0;
    this.angle = 0;
    this.levelExiting = false;
  }

  resurrect() {
    this.position = new Vector2D(80, WORLD_HEIGHT / 2 - 23);
    this.health = 100;
    this.bDying = false;
    this.bDead = false;
    this.dyingCounter = 0;
    this.invulnerable = true;
    this.invulnerableCounter = this.invulnerableTime;

    // Restore the sprite state clobbered by the explosion animation
    this.textureID = 'player';
    this.width = 101;
    this.height = 43;
    this.numFrames = 5;
    this.currentFrame = 0;
    this.frameTimer = 0;
    this.angle = 0;
    this.alpha = 1.0;
  }

  // Flies the helicopter out to the right once the level is beaten (Player::update)
  startLevelExit() {
    this.levelExiting = true;
    this.invulnerable = true;
    this.velocity.x = 3;
    this.velocity.y = 0;
    this.angle = 0;
    this.alpha = 1.0;
  }

  collision(type, game) {
    if (this.invulnerable || this.bDying || this.levelExiting) return;

    if (type === COLLISION_BULLET) {
      if (this.health > 10) {
        this.health -= 10;
        TheSoundManager.playSound('phaser');
      } else {
        this.startDying(game);
      }
    } else if (type === COLLISION_POWERUP) {
      TheSoundManager.playSound('powerup');
      if (game.lives < 3) {
        game.lives++;
      } else {
        this.health = 100;
      }
    } else {
      this.startDying(game);
    }
  }

  startDying(game) {
    this.bDying = true;
    this.dyingCounter = 0;
    this.dyingTime = 600;
    this.textureID = 'largeexplosion';
    this.numFrames = 9;
    this.width = 60;
    this.height = 60;
    TheSoundManager.playSound('boom');
  }

  update(dt, game) {
    if (this.levelExiting) {
      this.frameTimer += dt;
      if (this.frameTimer > 80) {
        this.frameTimer = 0;
        this.currentFrame = (this.currentFrame + 1) % this.numFrames;
      }
      this.position.x += this.velocity.x;
      return;
    }

    if (this.bDying) {
      this.dyingCounter += dt;
      this.currentFrame = Math.floor((this.dyingCounter / this.dyingTime) * this.numFrames);
      if (this.dyingCounter >= this.dyingTime) {
        this.bDead = true;
      }
      return;
    }

    if (this.invulnerable) {
      this.invulnerableCounter -= dt;
      if (this.invulnerableCounter <= 0) {
        this.invulnerable = false;
        this.alpha = 1.0;
      } else {
        this.alpha = Math.floor(this.invulnerableCounter / 120) % 2 === 0 ? 0.2 : 1.0;
      }
    }

    this.frameTimer += dt;
    if (this.frameTimer > 80) {
      this.frameTimer = 0;
      this.currentFrame = (this.currentFrame + 1) % this.numFrames;
    }

    const input = game.input;
    this.velocity.x = 0;
    this.velocity.y = 0;

    if (input.isDown('arrowleft') || input.isDown('a')) this.velocity.x = -this.moveSpeed;
    if (input.isDown('arrowright') || input.isDown('d')) this.velocity.x = this.moveSpeed;
    if (input.isDown('arrowup') || input.isDown('w')) this.velocity.y = -this.moveSpeed;
    if (input.isDown('arrowdown') || input.isDown('s')) this.velocity.y = this.moveSpeed;

    if (this.velocity.y < 0) this.angle = -8;
    else if (this.velocity.y > 0) this.angle = 8;
    else this.angle = 0;

    this.position.x += this.velocity.x;
    this.position.y += this.velocity.y;

    this.position.x = Math.max(10, Math.min(WIDTH - this.width - 10, this.position.x));
    this.position.y = Math.max(0, Math.min(WORLD_HEIGHT - this.height, this.position.y));

    this.bulletCounter -= dt;
    if ((input.isDown(' ') || input.isDown('space')) && this.bulletCounter <= 0) {
      game.bulletHandler.addPlayerBullet(
        this.position.x + this.width - 10,
        this.position.y + this.height / 2 - 3,
        16,
        6,
        'bullet1',
        new Vector2D(12, 0)
      );
      this.bulletCounter = this.bulletFiringSpeed;
      TheSoundManager.playSound('phaser');
    }

    this.secondaryCounter -= dt;
    if (input.isDown('control') && this.secondaryCounter <= 0) {
      game.bulletHandler.addPlayerBullet(
        this.position.x + this.width - 10,
        this.position.y + 8,
        14,
        6,
        'bullet2',
        new Vector2D(11, -3)
      );
      game.bulletHandler.addPlayerBullet(
        this.position.x + this.width - 10,
        this.position.y + this.height - 14,
        14,
        6,
        'bullet2',
        new Vector2D(11, 3)
      );
      this.secondaryCounter = this.bulletFiringSpeed * 1.4;
      TheSoundManager.playSound('laser2');
    }
  }

  draw(ctx) {
    if (this.bDying) {
      TheTextureManager.drawFrame(
        this.textureID,
        this.position.x,
        this.position.y,
        this.width,
        this.height,
        0,
        Math.min(this.numFrames - 1, this.currentFrame),
        ctx,
        0,
        1.0
      );
      return;
    }

    TheTextureManager.drawFrame(
      'player',
      this.position.x,
      this.position.y,
      this.width,
      this.height,
      0,
      this.currentFrame,
      ctx,
      this.angle,
      this.alpha
    );

    this.drawHealthBar(ctx);
  }
}


