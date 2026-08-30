import { BaseState } from './BaseState.js';
import { stateNames, difficulties } from '../config.js';

export class SettingsState extends BaseState {
  getStateID() {
    return stateNames.SETTINGS;
  }

  constructor() {
    super();
    this.diffOptions = [difficulties.EASY, difficulties.NORMAL, difficulties.HARD];
  }

  update(dt) {
    const input = this.game.input;
    if (input.consumeKey('arrowright', 'd')) {
      const idx = this.diffOptions.indexOf(this.game.difficulty);
      this.game.difficulty = this.diffOptions[(idx + 1) % this.diffOptions.length];
      input.keys.delete('arrowright');
      input.keys.delete('d');
    }

    if (input.consumeKey('arrowleft', 'a')) {
      const idx = this.diffOptions.indexOf(this.game.difficulty);
      this.game.difficulty = this.diffOptions[(idx - 1 + this.diffOptions.length) % this.diffOptions.length];
      input.keys.delete('arrowleft');
      input.keys.delete('a');
    }

    if (input.consumeKey('enter', 'escape')) {
      this.game.changeState(stateNames.MAIN_MENU);
    }
  }

  render(ctx) {
    ctx.fillStyle = '#071923';
    ctx.fillRect(0, 0, 960, 540);

    ctx.fillStyle = 'rgba(13, 32, 48, 0.85)';
    ctx.fillRect(150, 100, 660, 340);

    ctx.fillStyle = '#edf7ff';
    ctx.font = 'bold 36px Segoe UI';
    ctx.textAlign = 'center';
    ctx.fillText('SETTINGS', 480, 160);

    ctx.font = '22px Segoe UI';
    ctx.fillText('Music: Enabled', 480, 220);
    ctx.fillText('Sound FX: Enabled', 480, 260);

    ctx.fillStyle = '#5ad1ff';
    ctx.font = 'bold 24px Segoe UI';
    ctx.fillText(`Difficulty: < ${this.game.difficulty} >`, 480, 310);

    ctx.font = '18px Segoe UI';
    ctx.fillStyle = '#ffd166';
    ctx.fillText('Use Left/Right to change difficulty. Press ENTER to save.', 480, 380);
  }
}

