import { BaseState } from './BaseState.js';
import { stateNames } from '../config.js';

export class LevelCompleteState extends BaseState {
  getStateID() {
    return stateNames.LEVEL_COMPLETE;
  }

  update(dt) {
    if (this.game.input.isDown('enter') || this.game.input.isDown(' ') || this.game.input.isDown('space')) {
      this.game.level++;
      this.game.changeState(stateNames.LEVEL_OBJECTIVE);
    }
  }

  render(ctx) {
    ctx.fillStyle = '#071923';
    ctx.fillRect(0, 0, 960, 540);

    ctx.fillStyle = 'rgba(12, 34, 48, 0.85)';
    ctx.fillRect(200, 120, 560, 300);

    ctx.textAlign = 'center';
    ctx.fillStyle = '#7ae582';
    ctx.font = 'bold 44px Segoe UI';
    ctx.fillText('LEVEL COMPLETE!', 480, 200);

    ctx.fillStyle = '#edf7ff';
    ctx.font = '24px Segoe UI';
    ctx.fillText(`Score: ${this.game.score}`, 480, 260);

    ctx.fillStyle = '#ffd166';
    ctx.font = '20px Segoe UI';
    ctx.fillText('Press ENTER to proceed to next level', 480, 340);
  }
}
