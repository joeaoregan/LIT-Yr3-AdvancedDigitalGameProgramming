import { BaseState } from './BaseState.js';
import { stateNames } from '../config.js';

export class InstructionsState extends BaseState {
  getStateID() {
    return stateNames.INSTRUCTIONS;
  }

  update(dt) {
    if (this.game.input.consumeKey('escape', 'enter')) {
      this.game.changeState(stateNames.MAIN_MENU);
    }
  }

  render(ctx) {
    ctx.fillStyle = '#071923';
    ctx.fillRect(0, 0, 960, 540);

    ctx.fillStyle = 'rgba(13, 32, 48, 0.85)';
    ctx.fillRect(120, 80, 720, 380);

    ctx.fillStyle = '#edf7ff';
    ctx.font = 'bold 36px Segoe UI';
    ctx.textAlign = 'center';
    ctx.fillText('HOW TO PLAY', 480, 140);

    ctx.font = '20px Segoe UI';
    ctx.fillStyle = '#b9d9f0';
    ctx.fillText('Movement: Arrow Keys or WASD', 480, 200);
    ctx.fillText('Primary Fire: SPACE', 480, 240);
    ctx.fillText('Secondary Fire: CTRL', 480, 280);
    ctx.fillText('Pause Game: ESC or P', 480, 320);

    ctx.fillStyle = '#9ce8ff';
    ctx.font = '18px Segoe UI';
    ctx.fillText('Collect green PowerUps for lives/health. Press ESC to return.', 480, 390);
  }
}

