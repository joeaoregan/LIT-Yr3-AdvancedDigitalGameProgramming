export class InputHandler {
  constructor() {
    this.keys = new Set();
    // Keys pressed since the last consumeKey() call, so a held key fires once
    this.pressed = new Set();
    this.pointer = { x: 0, y: 0, down: false };
  }

  normalizeKey(key) {
    if (key === ' ') return 'space';
    if (key === 'Spacebar') return 'space';
    if (key.startsWith('Arrow')) {
      return `arrow${key.slice(5).toLowerCase()}`;
    }
    return key.toLowerCase();
  }

  bind(canvas) {
    window.addEventListener('keydown', (event) => {
      const key = this.normalizeKey(event.key);
      if (!this.keys.has(key)) {
        this.pressed.add(key);
      }
      this.keys.add(key);
      if (['ArrowUp', 'ArrowDown', 'ArrowLeft', 'ArrowRight', ' '].includes(event.key)) {
        event.preventDefault();
      }
    });

    window.addEventListener('keyup', (event) => {
      const key = this.normalizeKey(event.key);
      this.keys.delete(key);
    });

    canvas.addEventListener('mousemove', (event) => {
      const rect = canvas.getBoundingClientRect();
      this.pointer.x = ((event.clientX - rect.left) / rect.width) * canvas.width;
      this.pointer.y = ((event.clientY - rect.top) / rect.height) * canvas.height;
    });

    canvas.addEventListener('mousedown', () => {
      this.pointer.down = true;
    });

    canvas.addEventListener('mouseup', () => {
      this.pointer.down = false;
    });
  }

  isDown(key) {
    return this.keys.has(this.normalizeKey(key));
  }

  isPressed(key) {
    return this.keys.has(this.normalizeKey(key));
  }

  consumeKey(...keys) {
    for (const key of keys) {
      const normalized = this.normalizeKey(key);
      if (this.pressed.delete(normalized)) {
        return true;
      }
    }
    return false;
  }

  clearPressed() {
    this.pressed.clear();
  }

  consumePointerClick() {
    const wasDown = this.pointer.down;
    this.pointer.down = false;
    return wasDown;
  }
}
