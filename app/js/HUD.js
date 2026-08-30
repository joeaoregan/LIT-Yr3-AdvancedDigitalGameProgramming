import { WIDTH, HEIGHT, HUD_HEIGHT } from './config.js';

export class HUD {
  render(ctx, game) {
    ctx.save();

    // Top HUD bar
    ctx.fillStyle = 'rgba(6, 17, 26, 0.82)';
    ctx.fillRect(0, 0, WIDTH, HUD_HEIGHT);

    ctx.strokeStyle = 'rgba(255, 255, 255, 0.15)';
    ctx.beginPath();
    ctx.moveTo(0, HUD_HEIGHT);
    ctx.lineTo(WIDTH, HUD_HEIGHT);
    ctx.stroke();

    ctx.font = 'bold 18px Segoe UI';
    ctx.fillStyle = '#edf7ff';
    ctx.textAlign = 'left';

    ctx.fillText(`SCORE: ${game.score}`, 18, 30);
    ctx.fillText(`LIVES: ${game.lives}`, 220, 30);
    ctx.fillText(`LEVEL: ${game.level}`, 380, 30);
    ctx.fillText(`BEST: ${game.bestScore}`, 540, 30);
    ctx.fillText(`MODE: ${game.difficulty || 'NORMAL'}`, 720, 30);

    ctx.restore();
  }
}
