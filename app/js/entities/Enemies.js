import { ShooterObject } from '../GameObject.js';
import { Vector2D } from '../Vector2D.js';
import { WORLD_HEIGHT } from '../config.js';
import { TheTextureManager } from '../TextureManager.js';
import { TheSoundManager } from '../SoundManager.js';

export class Glider extends ShooterObject {
  constructor(x, y) {
    super();
    this.typeStr = 'Glider';
    this.textureID = 'enemy1';
    this.position = new Vector2D(x, y);
    this.velocity = new Vector2D(-3.2, 0);
    this.width = 42;
    this.height = 36;
    this.health = 20;
    this.maxHealth = 20;
    this.numFrames = 1;
  }

  draw(ctx) {
    if (this.bDying) return;
    TheTextureManager.drawFrame(this.textureID, this.position.x, this.position.y, this.width, this.height, 0, 0, ctx);
    this.drawHealthBar(ctx);
  }
}

export class AngryGlider extends ShooterObject {
  constructor(x, y) {
    super();
    this.typeStr = 'AngryGlider';
    this.textureID = 'angryenemy';
    this.position = new Vector2D(x, y);
    this.velocity = new Vector2D(-3.8, (Math.random() - 0.5) * 3);
    this.width = 42;
    this.height = 36;
    this.health = 30;
    this.maxHealth = 30;
    this.numFrames = 1;
  }

  update(dt, game) {
    super.update(dt);
    if (this.position.y <= 0 || this.position.y >= WORLD_HEIGHT - this.height) {
      this.velocity.y *= -1;
    }
  }

  draw(ctx) {
    if (this.bDying) return;
    TheTextureManager.drawFrame(this.textureID, this.position.x, this.position.y, this.width, this.height, 0, 0, ctx);
    this.drawHealthBar(ctx);
  }
}

export class ShotGlider extends ShooterObject {
  constructor(x, y) {
    super();
    this.typeStr = 'ShotGlider';
    this.textureID = 'enemy2';
    this.position = new Vector2D(x, y);
    this.velocity = new Vector2D(-2.5, 0);
    this.width = 44;
    this.height = 38;
    this.health = 30;
    this.maxHealth = 30;
    this.fireTimer = 0;
    this.fireInterval = 1500;
  }

  update(dt, game) {
    super.update(dt);
    this.fireTimer += dt;
    if (this.fireTimer >= this.fireInterval) {
      this.fireTimer = 0;
      if (game && game.bulletHandler) {
        game.bulletHandler.addEnemyBullet(
          this.position.x,
          this.position.y + this.height / 2 - 3,
          14,
          6,
          'bullet3',
          new Vector2D(-9, 0)
        );
      }
    }
  }

  draw(ctx) {
    if (this.bDying) return;
    TheTextureManager.drawFrame(this.textureID, this.position.x, this.position.y, this.width, this.height, 0, 0, ctx);
    this.drawHealthBar(ctx);
  }
}

export class Turret extends ShooterObject {
  constructor(x, y) {
    super();
    this.typeStr = 'Turret';
    this.textureID = 'turret';
    this.position = new Vector2D(x, y);
    this.velocity = new Vector2D(0, 0);
    this.scrollsWithMap = true;
    this.width = 52;
    this.height = 56;
    this.health = 40;
    this.maxHealth = 40;
    this.fireTimer = 0;
    this.fireInterval = 830;
  }

  update(dt, game) {
    super.update(dt);
    this.fireTimer += dt;
    if (this.fireTimer >= this.fireInterval) {
      this.fireTimer = 0;
      if (game?.bulletHandler) {
        // Three-way arc aimed up out of the ground emplacement
        game.bulletHandler.addEnemyBullet(this.position.x, this.position.y, 16, 16, 'bullet2', new Vector2D(-3, -3));
        game.bulletHandler.addEnemyBullet(this.position.x + 20, this.position.y, 16, 16, 'bullet2', new Vector2D(0, -3));
        game.bulletHandler.addEnemyBullet(this.position.x + 40, this.position.y, 16, 16, 'bullet2', new Vector2D(3, -3));
      }
    }
  }

  draw(ctx) {
    if (this.bDying) return;
    TheTextureManager.drawFrame(this.textureID, this.position.x, this.position.y, this.width, this.height, 0, 0, ctx);
    this.drawHealthBar(ctx);
  }
}

export class RoofTurret extends ShooterObject {
  constructor(x, y) {
    super();
    this.typeStr = 'RoofTurret';
    this.textureID = 'turret';
    this.position = new Vector2D(x, y);
    this.velocity = new Vector2D(0, 0);
    this.scrollsWithMap = true;
    this.width = 52;
    this.height = 56;
    this.health = 40;
    this.maxHealth = 40;
    this.fireTimer = 0;
    this.fireInterval = 830;
  }

  update(dt, game) {
    super.update(dt);
    this.fireTimer += dt;
    if (this.fireTimer >= this.fireInterval) {
      this.fireTimer = 0;
      if (game?.bulletHandler) {
        // Three-way arc aimed down out of the ceiling emplacement
        game.bulletHandler.addEnemyBullet(this.position.x, this.position.y + 20, 16, 16, 'bullet2', new Vector2D(-3, 3));
        game.bulletHandler.addEnemyBullet(this.position.x + 20, this.position.y + 20, 16, 16, 'bullet2', new Vector2D(0, 3));
        game.bulletHandler.addEnemyBullet(this.position.x + 40, this.position.y + 20, 16, 16, 'bullet2', new Vector2D(3, 3));
      }
    }
  }

  draw(ctx) {
    if (this.bDying) return;
    // Rotating 180 and mirroring horizontally gives SDL_FLIP_VERTICAL
    TheTextureManager.drawFrame(this.textureID, this.position.x, this.position.y, this.width, this.height, 0, 0, ctx, 180, 1.0, true);
    this.drawHealthBar(ctx);
  }
}

export class Level1Boss extends ShooterObject {
  constructor(x, y) {
    super();
    this.typeStr = 'Level1Boss';
    this.textureID = 'boss';
    this.position = new Vector2D(x, y);
    this.velocity = new Vector2D(0, 1.8);
    this.width = 180;
    this.height = 110;
    this.health = 400;
    this.maxHealth = 400;
    this.fireTimer = 0;
    this.fireInterval = 850;
  }

  update(dt, game) {
    super.update(dt);
    if (this.position.y <= 0 || this.position.y >= WORLD_HEIGHT - this.height) {
      this.velocity.y *= -1;
    }

    this.fireTimer += dt;
    if (this.fireTimer >= this.fireInterval) {
      this.fireTimer = 0;
      if (game && game.bulletHandler) {
        game.bulletHandler.addEnemyBullet(
          this.position.x,
          this.position.y + 20,
          18,
          8,
          'bullet4',
          new Vector2D(-9, -2)
        );
        game.bulletHandler.addEnemyBullet(
          this.position.x,
          this.position.y + this.height / 2,
          18,
          8,
          'bullet4',
          new Vector2D(-10, 0)
        );
        game.bulletHandler.addEnemyBullet(
          this.position.x,
          this.position.y + this.height - 28,
          18,
          8,
          'bullet4',
          new Vector2D(-9, 2)
        );
      }
    }
  }

  draw(ctx) {
    if (this.bDying) return;
    TheTextureManager.drawFrame(this.textureID, this.position.x, this.position.y, this.width, this.height, 0, 0, ctx);

    // Boss top health bar
    ctx.fillStyle = 'rgba(0,0,0,0.7)';
    ctx.fillRect(200, 12, 560, 16);
    ctx.fillStyle = '#ff5c7a';
    ctx.fillRect(200, 12, 560 * (this.health / this.maxHealth), 16);
    ctx.strokeStyle = '#ffffff';
    ctx.strokeRect(200, 12, 560, 16);
  }
}

export class PowerUp extends ShooterObject {
  constructor(x, y) {
    super();
    this.typeStr = 'PowerUp';
    this.textureID = 'powerUpID';
    this.position = new Vector2D(x, y);
    this.velocity = new Vector2D(-2.0, 0);
    this.width = 50;
    this.height = 20;
    this.health = 1;
    this.maxHealth = 1;
  }

  draw(ctx) {
    if (this.bDying) return;
    TheTextureManager.drawFrame(this.textureID, this.position.x, this.position.y, this.width, this.height, 0, 0, ctx);
  }
}

// Rises and falls between two map rows, blocking the corridor (Pounder.h)
export class Pounder extends ShooterObject {
  constructor(x, y) {
    super();
    this.typeStr = 'Pounder';
    this.textureID = 'pounder';
    this.position = new Vector2D(x, y);
    this.velocity = new Vector2D(0, 0);
    this.scrollsWithMap = true;
    // Pounder.h overrides collision() to take no damage
    this.indestructible = true;
    this.width = 64;
    this.height = 128;
    this.health = 30;
    this.maxHealth = 30;
    this.topY = 224;
    this.bottomY = 352;
    this.dropSpeed = 2;
    this.riseSpeed = -8;
    this.falling = this.position.y <= this.topY;
  }

  update(dt, game) {
    if (!this.bDying) {
      if (this.position.y >= this.bottomY) {
        this.position.y = this.bottomY;
        this.falling = false;
      } else if (this.position.y <= this.topY) {
        this.position.y = this.topY;
        this.falling = true;
      }
      this.velocity.y = this.falling ? this.dropSpeed : this.riseSpeed;
    }
    super.update(dt);
  }

  draw(ctx) {
    if (this.bDying) return;
    TheTextureManager.drawFrame(this.textureID, this.position.x, this.position.y, this.width, this.height, 0, 0, ctx);
  }
}

// Slams down from the ceiling then retracts (Squasher.h)
export class Squasher extends ShooterObject {
  constructor(x, y) {
    super();
    this.typeStr = 'Squasher';
    this.textureID = 'squasher';
    this.position = new Vector2D(x, y);
    this.velocity = new Vector2D(0, 0);
    this.scrollsWithMap = true;
    // Squasher.h overrides collision() to take no damage
    this.indestructible = true;
    this.width = 64;
    this.height = 128;
    this.health = 30;
    this.maxHealth = 30;
    this.topY = -32;
    this.bottomY = 96;
    this.dropSpeed = 8;
    this.riseSpeed = -2;
    this.falling = true;
  }

  update(dt, game) {
    if (!this.bDying) {
      if (this.position.y >= this.bottomY) {
        this.position.y = this.bottomY;
        if (this.falling) {
          TheSoundManager.playSound('blast');
        }
        this.falling = false;
      } else if (this.position.y <= this.topY) {
        this.position.y = this.topY;
        this.falling = true;
      }
      this.velocity.y = this.falling ? this.dropSpeed : this.riseSpeed;
    }
    super.update(dt);
  }

  draw(ctx) {
    if (this.bDying) return;
    TheTextureManager.drawFrame(this.textureID, this.position.x, this.position.y, this.width, this.height, 0, 0, ctx);
  }
}

// Drops down the screen firing sideways (Eskeletor.h)
export class Eskeletor extends ShooterObject {
  constructor(x, y) {
    super();
    this.typeStr = 'Eskeletor';
    this.textureID = 'enemy3';
    this.position = new Vector2D(x, y);
    this.velocity = new Vector2D(0, 3);
    this.scrollsWithMap = true;
    this.width = 34;
    this.height = 35;
    this.health = 30;
    this.maxHealth = 30;
    this.numFrames = 3;
    this.frameTimer = 0;
    this.fireTimer = 0;
    this.fireInterval = 830;
  }

  update(dt, game) {
    if (!this.bDying) {
      this.frameTimer += dt;
      if (this.frameTimer > 120) {
        this.frameTimer = 0;
        this.currentFrame = (this.currentFrame + 1) % this.numFrames;
      }

      this.fireTimer += dt;
      if (this.fireTimer >= this.fireInterval) {
        this.fireTimer = 0;
        if (game && game.bulletHandler) {
          game.bulletHandler.addEnemyBullet(this.position.x, this.position.y, 16, 16, 'bullet1', new Vector2D(-3, 0));
          game.bulletHandler.addEnemyBullet(this.position.x, this.position.y, 16, 16, 'bullet1', new Vector2D(3, 0));
        }
      }
    }
    super.update(dt);
  }

  draw(ctx) {
    if (this.bDying) return;
    TheTextureManager.drawFrame(this.textureID, this.position.x, this.position.y, this.width, this.height, 0, this.currentFrame, ctx);
    this.drawHealthBar(ctx);
  }
}

