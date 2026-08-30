import { BaseState } from './BaseState.js';
import { stateNames } from '../config.js';

export class EnterNameState extends BaseState {
  getStateID() {
    return stateNames.ENTER_NAME;
  }

  enter() {
    this.nameBuffer = this.game.playerName || 'PLAYER';
  }

  update(dt) {
    if (this.game.input.isDown('enter')) {
      this.game.playerName = this.nameBuffer || 'PLAYER';
      this.game.addHighScore(this.game.playerName, this.game.score);
      this.game.changeState(stateNames.HIGH_SCORE);
    }
  }

  render(ctx) {
    ctx.fillStyle = '#071923';
    ctx.fillRect(0, 0, 960, 540);

    ctx.fillStyle = 'rgba(12, 34, 48, 0.85)';
    ctx.fillRect(200, 120, 560, 300);

    ctx.textAlign = 'center';
    ctx.fillStyle = '#edf7ff';
    ctx.font = 'bold 36px Segoe UI';
    ctx.fillText('NEW HIGH SCORE!', 480, 180);

    ctx.font = '22px Segoe UI';
    ctx.fillText(`Final Score: ${this.game.score}`, 480, 230);

    ctx.fillStyle = '#5ad1ff';
    ctx.font = 'bold 28px Segoe UI';
    ctx.fillText(`NAME: ${this.nameBuffer}`, 480, 290);

    ctx.fillStyle = '#ffd166';
    ctx.font = '20px Segoe UI';
    ctx.fillText('Press ENTER to Submit', 480, 370);
  }
}
