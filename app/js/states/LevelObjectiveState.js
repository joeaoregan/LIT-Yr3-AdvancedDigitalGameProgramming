import { BaseState } from './BaseState.js';
import { stateNames } from '../config.js';

export class LevelObjectiveState extends BaseState {
  getStateID() {
    return stateNames.LEVEL_OBJECTIVE;
  }

  enter() {
    this.timer = 3000;
  }

  update(dt) {
    this.timer -= dt;
    if (this.timer <= 0 || this.game.input.consumeKey('enter', 'space')) {
      this.game.changeState(stateNames.PLAY);
    }
  }

  render(ctx) {
    ctx.fillStyle = '#071923';
    ctx.fillRect(0, 0, 960, 540);

    ctx.fillStyle = 'rgba(12, 34, 48, 0.85)';
    ctx.fillRect(180, 120, 600, 300);

    ctx.textAlign = 'center';
    ctx.fillStyle = '#edf7ff';
    ctx.font = 'bold 40px Segoe UI';
    ctx.fillText(`LEVEL ${this.game.level} OBJECTIVE`, 480, 190);

    ctx.font = '22px Segoe UI';
    ctx.fillStyle = '#9ce8ff';
    ctx.fillText('Destroy all enemy forces and defeat the Level Boss!', 480, 260);

    ctx.font = '18px Segoe UI';
    ctx.fillStyle = '#ffd166';
    ctx.fillText('Press SPACE or wait to engage...', 480, 350);
  }
}
