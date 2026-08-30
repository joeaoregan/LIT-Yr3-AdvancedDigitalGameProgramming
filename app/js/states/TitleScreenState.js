import { BaseState } from './BaseState.js';
import { stateNames } from '../config.js';
import { TheTextureManager } from '../TextureManager.js';

export class TitleScreenState extends BaseState {
  getStateID() {
    return stateNames.TITLE_SCREEN;
  }

  update(dt) {
    const input = this.game.input;
    if (input.consumeKey('enter', 'space') || input.consumePointerClick()) {
      this.game.changeState(stateNames.MAIN_MENU);
    }
  }

  render(ctx) {
    ctx.fillStyle = '#071923';
    ctx.fillRect(0, 0, 960, 540);

    const titleBg = TheTextureManager.getTexture('titlebg');
    if (titleBg) {
      // Letterbox the 800x640 backdrop instead of stretching it to 16:9
      const scale = 540 / titleBg.naturalHeight;
      const w = titleBg.naturalWidth * scale;
      TheTextureManager.draw('titlebg', (960 - w) / 2, 0, w, 540, ctx);
    } else {
      ctx.fillStyle = 'rgba(12, 34, 48, 0.85)';
      ctx.fillRect(180, 100, 600, 340);

      ctx.textAlign = 'center';
      ctx.fillStyle = '#edf7ff';
      ctx.font = 'bold 52px Segoe UI';
      ctx.fillText('ALIEN ATTACK', 480, 200);
    }

    const anyKey = TheTextureManager.getTexture('anykey');
    if (anyKey) {
      // anykey.png is a 3-frame sheet, so draw a single frame scaled up and centred
      const size = TheTextureManager.getFrameSize('anykey', 1.5);
      TheTextureManager.drawFrame('anykey', (960 - size.width) / 2, 430, size.width, size.height, 0, 0, ctx);
    } else {
      ctx.textAlign = 'center';
      ctx.fillStyle = '#ffd166';
      ctx.font = 'bold 24px Segoe UI';
      ctx.fillText('PRESS ENTER OR CLICK TO START', 480, 450);
    }
  }
}

