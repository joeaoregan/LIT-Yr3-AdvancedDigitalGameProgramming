import { BaseState } from './BaseState.js';
import { stateNames } from '../config.js';
import { TheTextureManager } from '../TextureManager.js';

export class TitleScreenState extends BaseState {
  constructor(game) {
    super(game);
    this.animTimer = 0;
    this.animSpeed = 200; // ms per frame (increase to slow down, decrease to speed up)
    this.currentSeqIndex = 0;
    this.animSequence = [0, 1, 2, 1, 0];
  }

  getStateID() {
    return stateNames.TITLE_SCREEN;
  }

  update(dt) {
    const input = this.game.input;
    if (input.consumeKey('enter', 'space') || input.consumePointerClick()) {
      this.game.changeState(stateNames.MAIN_MENU);
    }

    this.animTimer += dt;
    if (this.animTimer >= this.animSpeed) {
      this.animTimer = 0;
      this.currentSeqIndex = (this.currentSeqIndex + 1) % this.animSequence.length;
    }
  }

  render(ctx) {
    ctx.fillStyle = '#071923';
    ctx.fillRect(0, 0, 960, 540);

    const titleBg = TheTextureManager.getTexture('titlebg');
    if (titleBg) {
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
      const size = TheTextureManager.getFrameSize('anykey', 1.8);
      const currentFrame = this.animSequence[this.currentSeqIndex];

      // anykey.png is a single row of 3 frames, so the index is the column
      TheTextureManager.drawFrame(
        'anykey',
        (960 - size.width) / 2,
        275,
        size.width,
        size.height,
        0,
        currentFrame,
        ctx
      );
    } else {
      ctx.textAlign = 'center';
      ctx.fillStyle = '#ffd166';
      ctx.font = 'bold 24px Segoe UI';
      ctx.fillText('PRESS ENTER OR CLICK TO START', 480, 450);
    }
  }
}