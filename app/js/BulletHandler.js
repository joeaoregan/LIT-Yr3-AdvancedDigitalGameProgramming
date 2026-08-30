import { Vector2D } from './Vector2D.js';
import { WIDTH, WORLD_HEIGHT } from './config.js';
import { TheTextureManager } from './TextureManager.js';

export class Bullet {
  constructor(x, y, width, height, textureID, heading, owner = 'player') {
    this.position = new Vector2D(x, y);
    this.velocity = new Vector2D(heading.x, heading.y);
    this.width = width;
    this.height = height;
    this.textureID = textureID;
    this.owner = owner;
    this.bDead = false;
  }

  update(dt) {
    this.position.x += this.velocity.x;
    this.position.y += this.velocity.y;

    if (
      this.position.x < -50 ||
      this.position.x > WIDTH + 50 ||
      this.position.y < -50 ||
      this.position.y > WORLD_HEIGHT + 50
    ) {
      this.bDead = true;
    }
  }

  draw(ctx) {
    const img = TheTextureManager.getTexture(this.textureID);
    if (img) {
      TheTextureManager.draw(this.textureID, this.position.x, this.position.y, this.width, this.height, ctx);
    } else {
      ctx.fillStyle = this.owner === 'player' ? '#7ae582' : '#ff8fab';
      ctx.fillRect(this.position.x, this.position.y, this.width, this.height);
    }
  }
}

export class BulletHandler {
  constructor() {
    this.playerBullets = [];
    this.enemyBullets = [];
  }

  addPlayerBullet(x, y, width = 16, height = 6, textureID = 'bullet1', heading = new Vector2D(12, 0)) {
    this.playerBullets.push(new Bullet(x, y, width, height, textureID, heading, 'player'));
  }

  addEnemyBullet(x, y, width = 14, height = 6, textureID = 'bullet3', heading = new Vector2D(-9, 0)) {
    this.enemyBullets.push(new Bullet(x, y, width, height, textureID, heading, 'enemy'));
  }

  updateBullets(dt) {
    this.playerBullets.forEach((b) => b.update(dt));
    this.enemyBullets.forEach((b) => b.update(dt));

    this.playerBullets = this.playerBullets.filter((b) => !b.bDead);
    this.enemyBullets = this.enemyBullets.filter((b) => !b.bDead);
  }

  drawBullets(ctx) {
    this.playerBullets.forEach((b) => b.draw(ctx));
    this.enemyBullets.forEach((b) => b.draw(ctx));
  }

  clearBullets() {
    this.playerBullets = [];
    this.enemyBullets = [];
  }
}

