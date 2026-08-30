import { BaseState } from './BaseState.js';
import { stateNames } from '../config.js';
import { TheTextureManager } from '../TextureManager.js';
import { TheSoundManager } from '../SoundManager.js';

export class MainMenuState extends BaseState {
  getStateID() {
    return stateNames.MAIN_MENU;
  }

  constructor() {
    super();
    // Centered button bounds for 960x540 canvas
    this.buttons = [
      { id: 'playbutton', label: 'Start Game', x: 310, y: 140, w: 340, h: 68, action: () => { this.game.resetRun(); this.game.changeState(stateNames.LEVEL_OBJECTIVE); } },
      { id: 'scorebutton', label: 'High Scores', x: 310, y: 220, w: 340, h: 68, action: () => this.game.changeState(stateNames.HIGH_SCORE) },
      { id: 'settingsbutton', label: 'Settings', x: 310, y: 300, w: 340, h: 68, action: () => this.game.changeState(stateNames.SETTINGS) },
      { id: 'instructionsbutton', label: 'How to Play', x: 310, y: 380, w: 340, h: 68, action: () => this.game.changeState(stateNames.INSTRUCTIONS) }
    ];
    this.hovered = null;
    this.selected = 0;
  }

  enter() {
    this.hovered = null;
    this.selected = 0;
    this.game.input.clearPressed();
  }

  update(dt) {
    const { input } = this.game;
    const mx = input.pointer.x;
    const my = input.pointer.y;

    const underPointer = this.buttons.find((button) =>
      mx >= button.x && mx <= button.x + button.w && my >= button.y && my <= button.y + button.h
    ) || null;

    if (underPointer && underPointer !== this.hovered) {
      this.selected = this.buttons.indexOf(underPointer);
    }
    this.hovered = underPointer;

    if (input.consumeKey('arrowup', 'w')) {
      this.selected = (this.selected - 1 + this.buttons.length) % this.buttons.length;
      this.hovered = null;
      TheSoundManager.playSound('button');
    }

    if (input.consumeKey('arrowdown', 's')) {
      this.selected = (this.selected + 1) % this.buttons.length;
      this.hovered = null;
      TheSoundManager.playSound('button');
    }

    if (input.consumeKey('enter', 'space')) {
      TheSoundManager.playSound('button');
      this.buttons[this.selected].action();
      return;
    }

    if (input.pointer.down && underPointer) {
      input.pointer.down = false;
      TheSoundManager.playSound('button');
      underPointer.action();
    }
  }

  render(ctx) {
    ctx.fillStyle = '#071923';
    ctx.fillRect(0, 0, 960, 540);

    // Draw background grid overlay
    ctx.fillStyle = 'rgba(12, 34, 48, 0.85)';
    ctx.fillRect(180, 20, 600, 500);

    // Draw original logo
    const logoImg = TheTextureManager.getTexture('attacklogo');
    if (logoImg) {
      TheTextureManager.draw('attacklogo', 260, 40, 440, 80, ctx);
    } else {
      ctx.textAlign = 'center';
      ctx.fillStyle = '#edf7ff';
      ctx.font = 'bold 44px Segoe UI';
      ctx.fillText('ALIEN ATTACK', 480, 90);
    }

    // Draw buttons
    this.buttons.forEach((button, index) => {
      const isHover = index === this.selected;

      const btnImg = TheTextureManager.getTexture(button.id);
      if (btnImg) {
        TheTextureManager.drawFrame(
          button.id,
          button.x,
          button.y,
          button.w,
          button.h,
          0,
          isHover ? 1 : 0,
          ctx
        );
      } else {
        ctx.fillStyle = isHover ? '#5ad1ff' : '#1d4059';
        ctx.fillRect(button.x, button.y, button.w, button.h);
        ctx.strokeStyle = '#a8d7ff';
        ctx.strokeRect(button.x, button.y, button.w, button.h);
        ctx.fillStyle = '#edf7ff';
        ctx.font = 'bold 22px Segoe UI';
        ctx.textAlign = 'center';
        ctx.fillText(button.label, button.x + button.w / 2, button.y + 42);
      }
    });
  }
}


