import { COLLISION_BULLET, COLLISION_ENEMY, COLLISION_POWERUP } from './entities/PlayerConsts.js';
import { TheSoundManager } from './SoundManager.js';

export class CollisionManager {
  boxOf(obj) {
    return obj.getHitBox ? obj.getHitBox() : { x: obj.position.x, y: obj.position.y, width: obj.width, height: obj.height };
  }

  rectIntersect(a, b) {
    const boxA = this.boxOf(a);
    const boxB = this.boxOf(b);
    return this.boxIntersect(boxA, boxB);
  }

  boxIntersect(a, b) {
    return (
      a.x < b.x + b.width &&
      a.x + a.width > b.x &&
      a.y < b.y + b.height &&
      a.y + a.height > b.y
    );
  }

  checkPlayerEnemyBulletCollision(player, bulletHandler, game) {
    if (!player || player.bDying || player.bDead || player.invulnerable) return;

    for (let i = bulletHandler.enemyBullets.length - 1; i >= 0; i--) {
      const b = bulletHandler.enemyBullets[i];
      if (this.rectIntersect(player, b)) {
        b.bDead = true;
        player.collision(COLLISION_BULLET, game);
        break;
      }
    }
  }

  checkPlayerEnemyCollision(player, enemies, game) {
    if (!player || player.bDying || player.bDead || player.invulnerable) return;

    for (let i = enemies.length - 1; i >= 0; i--) {
      const enemy = enemies[i];
      if (enemy.bDying || enemy.bDead || enemy.fading) continue;

      if (enemy.typeStr === 'PowerUp') {
        if (this.rectIntersect(player, enemy)) {
          enemy.bDead = true;
          player.collision(COLLISION_POWERUP, game);
        }
      } else {
        if (this.rectIntersect(player, enemy)) {
          if (!enemy.indestructible) {
            enemy.explode();
            TheSoundManager.playSound('boom');
          }
          player.collision(COLLISION_ENEMY, game);
        }
      }
    }
  }

  checkEnemyPlayerBulletCollision(enemies, bulletHandler, game) {
    for (let i = bulletHandler.playerBullets.length - 1; i >= 0; i--) {
      const bullet = bulletHandler.playerBullets[i];
      if (bullet.bDead) continue;

      for (let j = enemies.length - 1; j >= 0; j--) {
        const enemy = enemies[j];
        if (enemy.bDying || enemy.bDead || enemy.fading || enemy.typeStr === 'PowerUp') continue;

        if (this.rectIntersect(bullet, enemy)) {
          bullet.bDead = true;
          if (enemy.indestructible) break;

          // Armoured sections absorb the shot without taking damage
          if (!this.boxIntersect(this.boxOf(bullet), enemy.getDamageBox())) break;

          enemy.takeDamage(10);
          if (enemy.health <= 0) {
            game.score += enemy.maxHealth * 2;
            enemy.explode();
            TheSoundManager.playSound('boom');
          }
          break;
        }
      }
    }
  }

  checkPlayerTileCollision(player, tileLayers, scrollDistance, game) {
    if (!player || player.bDying || player.bDead || player.invulnerable) return;

    for (const layer of tileLayers) {
      const tileSize = layer.tileSize;
      const tileIDs = layer.tileIDs;
      if (!tileIDs || tileIDs.length === 0) continue;

      const worldX = player.position.x + scrollDistance;
      const startCol = Math.floor(worldX / tileSize);
      const endCol = Math.floor((worldX + player.width) / tileSize);
      const startRow = Math.floor(player.position.y / tileSize);
      const endRow = Math.floor((player.position.y + player.height) / tileSize);

      for (let r = startRow; r <= endRow; r++) {
        for (let c = startCol; c <= endCol; c++) {
          if (r >= 0 && r < layer.mapHeight && c >= 0 && c < layer.mapWidth) {
            const tileID = tileIDs[r][c];
            if (tileID !== 0) {
              player.collision(COLLISION_ENEMY, game);
              return;
            }
          }
        }
      }
    }
  }

  checkAll(player, enemies, bulletHandler, tileLayers, scrollDistance, game) {
    this.checkPlayerEnemyBulletCollision(player, bulletHandler, game);
    this.checkPlayerEnemyCollision(player, enemies, game);
    this.checkEnemyPlayerBulletCollision(enemies, bulletHandler, game);
    if (tileLayers && tileLayers.length > 0) {
      this.checkPlayerTileCollision(player, tileLayers, scrollDistance, game);
    }
  }
}


