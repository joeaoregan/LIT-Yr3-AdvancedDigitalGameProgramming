export class StateMachine {
  constructor(game) {
    this.game = game;
    this.stack = [];
  }

  pushState(state) {
    state.game = this.game;
    this.stack.push(state);
    state.enter();
  }

  popState() {
    if (this.stack.length > 0) {
      const top = this.stack.pop();
      top.exit();
    }
    if (this.stack.length > 0) {
      const current = this.stack[this.stack.length - 1];
      if (current.resume) current.resume();
    }
  }

  changeState(state) {
    if (this.stack.length > 0) {
      const current = this.stack[this.stack.length - 1];
      if (current.getStateID && state.getStateID && current.getStateID() === state.getStateID()) {
        return;
      }
      const top = this.stack.pop();
      top.exit();
    }
    state.game = this.game;
    state.enter();
    this.stack.push(state);
  }

  getCurrentState() {
    return this.stack.length > 0 ? this.stack[this.stack.length - 1] : null;
  }

  update(dt) {
    const current = this.getCurrentState();
    if (current && current.update) {
      current.update(dt);
    }
  }

  render(ctx) {
    const current = this.getCurrentState();
    if (current && current.render) {
      current.render(ctx);
    }
  }
}

