import { BaseState } from './BaseState.js';
import { stateNames } from '../config.js';

export class GameOverState extends BaseState {
  getStateID() {
    return stateNames.GAME_OVER;
  }

  update(dt) {
    if (this.game.input.isDown('enter')) {
      this.game.resetRun();
      this.game.changeState(stateNames.MAIN_MENU);
    }
  }

  render(ctx) {
    ctx.fillStyle = '#071923';
    ctx.fillRect(0, 0, 960, 540);

    ctx.fillStyle = 'rgba(15, 15, 20, 0.85)';
    ctx.fillRect(180, 140, 600, 260);

    ctx.fillStyle = '#ff5c7a';
    ctx.textAlign = 'center';
    ctx.font = 'bold 48px Segoe UI';
    ctx.fillText('GAME OVER', 480, 220);

    ctx.fillStyle = '#edf7ff';
    ctx.font = '24px Segoe UI';
    ctx.fillText(`Final Score: ${this.game.score}`, 480, 275);

    ctx.fillStyle = '#ffd166';
    ctx.font = '20px Segoe UI';
    ctx.fillText('Press ENTER to return to Main Menu', 480, 335);
  }
}

