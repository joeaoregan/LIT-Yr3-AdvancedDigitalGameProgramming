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

    // --- Touch Support for Mobile Drag & Directional Movement ---
    let touchStartX = 0;
    let touchStartY = 0;
    const dragThreshold = 15; // Minimum pixels moved to trigger directional movement

    canvas.addEventListener('touchstart', (event) => {
      event.preventDefault();
      if (event.touches.length > 0) {
        const touch = event.touches[0];
        touchStartX = touch.clientX;
        touchStartY = touch.clientY;
        
        const rect = canvas.getBoundingClientRect();
        this.pointer.x = ((touch.clientX - rect.left) / rect.width) * canvas.width;
        this.pointer.y = ((touch.clientY - rect.top) / rect.height) * canvas.height;
      }
      this.pointer.down = true;
      
      // Tap behavior for menus (space bar simulation)
      const spaceKey = 'space';
      if (!this.keys.has(spaceKey)) {
        this.pressed.add(spaceKey);
      }
      this.keys.add(spaceKey);
    }, { passive: false });

    canvas.addEventListener('touchmove', (event) => {
      event.preventDefault();
      if (event.touches.length === 0) return;

      const touch = event.touches[0];
      const deltaX = touch.clientX - touchStartX;
      const deltaY = touch.clientY - touchStartY;

      // Clear existing directional keys before re-evaluating vector drag
      this.keys.delete('arrowleft');
      this.keys.delete('arrowright');
      this.keys.delete('arrowup');
      this.keys.delete('arrowdown');

      // Check horizontal threshold for diagonals / left / right
      if (Math.abs(deltaX) > dragThreshold) {
        if (deltaX < 0) this.keys.add('arrowleft');
        else this.keys.add('arrowright');
      }

      // Check vertical threshold for diagonals / up / down
      if (Math.abs(deltaY) > dragThreshold) {
        if (deltaY < 0) this.keys.add('arrowup');
        else this.keys.add('arrowdown');
      }

      // Update pointer position for any click bounds if needed
      const rect = canvas.getBoundingClientRect();
      this.pointer.x = ((touch.clientX - rect.left) / rect.width) * canvas.width;
      this.pointer.y = ((touch.clientY - rect.top) / rect.height) * canvas.height;
    }, { passive: false });

    canvas.addEventListener('touchend', (event) => {
      event.preventDefault();
      this.pointer.down = false;
      
      // Clear movement keys and menu tap keys on release
      this.keys.delete('space');
      this.keys.delete('arrowleft');
      this.keys.delete('arrowright');
      this.keys.delete('arrowup');
      this.keys.delete('arrowdown');
    }, { passive: false });
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
