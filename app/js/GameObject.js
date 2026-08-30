import { Vector2D } from './Vector2D.js';
import { TheTextureManager } from './TextureManager.js';

export class GameObject {
  constructor() {
    this.position = new Vector2D(0, 0);
    this.velocity = new Vector2D(0, 0);
    this.width = 32;
    this.height = 32;
    this.numFrames = 1;
    this.currentRow = 0;
    this.currentFrame = 0;
    this.angle = 0;
    this.alpha = 1.0;
    this.textureID = '';
    this.bDying = false;
    this.bDead = false;
    // When true the object is anchored to the map and moves with the level scroll
    this.scrollsWithMap = false;
    this.typeStr = 'GameObject';
  }

  load(params) {
    this.position.x = params.x || 0;
    this.position.y = params.y || 0;
    this.width = params.width || 32;
    this.height = params.height || 32;
    this.textureID = params.textureID || '';
    this.numFrames = params.numFrames || 1;
  }

  update(dt) {
    this.position.x += this.velocity.x;
    this.position.y += this.velocity.y;
  }

  draw(ctx) {
    ctx.save();
    ctx.globalAlpha = this.alpha;
    ctx.fillStyle = '#52d1ff';
    ctx.fillRect(this.position.x, this.position.y, this.width, this.height);
    ctx.restore();
  }

  clean() {}
  collision() {}
  type() { return this.typeStr; }
}

export class ShooterObject extends GameObject {
  constructor() {
    super();
    this.bulletFiringSpeed = 0;
    this.bulletCounter = 0;
    this.moveSpeed = 0;
    this.dyingTime = 450;
    this.dyingCounter = 0;
    this.bPlayedDeathSound = false;
    this.health = 100;
    this.maxHealth = 100;
    // Explosion sheet swapped in on death, as the C++ collision() overrides do
    this.explosionID = 'explosion';
    this.explosionSize = 40;
    this.explosionFrames = 9;
    this.typeStr = 'ShooterObject';
  }

  update(dt) {
    if (this.bDying) {
      this.doDyingAnimation(dt);
      return;
    }
    super.update(dt);
  }

  explode() {
    if (this.bDying) return;

    this.bDying = true;
    this.dyingCounter = 0;
    this.currentFrame = 0;
    this.health = 0;
    this.velocity.x = 0;
    this.velocity.y = 0;

    // Keep the blast centred on the sprite it replaces
    this.position.x += (this.width - this.explosionSize) / 2;
    this.position.y += (this.height - this.explosionSize) / 2;

    this.textureID = this.explosionID;
    this.numFrames = this.explosionFrames;
    this.width = this.explosionSize;
    this.height = this.explosionSize;
  }

  doDyingAnimation(dt) {
    this.dyingCounter += dt;
    this.currentFrame = Math.min(
      this.numFrames - 1,
      Math.floor((this.dyingCounter / this.dyingTime) * this.numFrames)
    );
    if (this.dyingCounter >= this.dyingTime) {
      this.bDead = true;
    }
  }

  draw(ctx) {
    TheTextureManager.drawFrame(
      this.textureID,
      this.position.x,
      this.position.y,
      this.width,
      this.height,
      this.currentRow,
      this.currentFrame,
      ctx,
      this.angle,
      this.alpha
    );
    if (!this.bDying) {
      this.drawHealthBar(ctx);
    }
  }

  drawHealthBar(ctx, offsetX = 0, offsetY = -10) {
    if (this.bDying || this.bDead) return;
    const barWidth = this.width;
    const barHeight = 4;
    const x = this.position.x + offsetX;
    const y = this.position.y + this.height + 6 + offsetY;
    const pct = Math.max(0, Math.min(1, this.health / this.maxHealth));

    ctx.fillStyle = 'rgba(0, 0, 0, 0.6)';
    ctx.fillRect(x, y, barWidth, barHeight);

    ctx.fillStyle = pct > 0.5 ? '#7ae582' : pct > 0.25 ? '#ffd166' : '#ff5c7a';
    ctx.fillRect(x, y, barWidth * pct, barHeight);
  }
}
