import { BaseState } from './BaseState.js';
import { stateNames } from '../config.js';

export class HighScoreState extends BaseState {
  getStateID() {
    return stateNames.HIGH_SCORE;
  }

  update(dt) {
    if (this.game.input.consumeKey('escape', 'enter')) {
      this.game.changeState(stateNames.MAIN_MENU);
    }
  }

  render(ctx) {
    ctx.fillStyle = '#071923';
    ctx.fillRect(0, 0, 960, 540);

    ctx.fillStyle = 'rgba(12, 34, 48, 0.85)';
    ctx.fillRect(160, 60, 640, 420);

    ctx.textAlign = 'center';
    ctx.fillStyle = '#edf7ff';
    ctx.font = 'bold 36px Segoe UI';
    ctx.fillText('HIGH SCORES', 480, 110);

    ctx.font = '20px Segoe UI';
    const scores = this.game.highScores || [];
    scores.forEach((entry, idx) => {
      ctx.fillStyle = idx === 0 ? '#ffd166' : '#edf7ff';
      ctx.textAlign = 'left';
      ctx.fillText(`${idx + 1}.  ${entry.name}`, 300, 170 + idx * 28);
      ctx.textAlign = 'right';
      ctx.fillText(`${entry.score}`, 660, 170 + idx * 28);
    });

    ctx.textAlign = 'center';
    ctx.fillStyle = '#9ce8ff';
    ctx.font = '18px Segoe UI';
    ctx.fillText('Press Escape or Enter to return', 480, 450);
  }
}
