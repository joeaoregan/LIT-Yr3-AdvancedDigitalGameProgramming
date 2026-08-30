import { BaseState } from './BaseState.js';
import { stateNames } from '../config.js';

export class PauseState extends BaseState {
  getStateID() {
    return stateNames.PAUSE;
  }

  update(dt) {
    const input = this.game.input;
    if (input.consumeKey('escape', 'p')) {
      this.game.popState();
    }
  }

  render(ctx) {
    ctx.fillStyle = 'rgba(7, 25, 35, 0.75)';
    ctx.fillRect(0, 0, 960, 540);

    ctx.fillStyle = 'rgba(12, 34, 48, 0.9)';
    ctx.fillRect(280, 160, 400, 220);

    ctx.textAlign = 'center';
    ctx.fillStyle = '#edf7ff';
    ctx.font = 'bold 44px Segoe UI';
    ctx.fillText('PAUSED', 480, 240);

    ctx.font = '20px Segoe UI';
    ctx.fillStyle = '#9ce8ff';
    ctx.fillText('Press ESC or P to Resume', 480, 310);
  }
}
