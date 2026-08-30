export class TextureManager {
  constructor() {
    this.textures = new Map();
    // id -> { frameWidth, frameHeight } describing the source cell size of a sprite sheet
    this.frameSpecs = new Map();
    this.loadedCount = 0;
    this.totalCount = 0;
  }

  static getInstance() {
    if (!TextureManager.instance) {
      TextureManager.instance = new TextureManager();
    }
    return TextureManager.instance;
  }

  load(id, src, frameSpec = null) {
    if (frameSpec) {
      this.frameSpecs.set(id, frameSpec);
    }

    if (this.textures.has(id)) {
      return Promise.resolve(this.textures.get(id));
    }

    this.totalCount++;
    return new Promise((resolve) => {
      const img = new Image();
      img.onload = () => {
        this.textures.set(id, img);
        this.loadedCount++;
        resolve(img);
      };
      img.onerror = () => {
        console.warn(`Failed to load texture: ${id} at ${src}`);
        this.loadedCount++;
        resolve(null);
      };
      img.src = src;
    });
  }

  getTexture(id) {
    return this.textures.get(id) || null;
  }

  setFrameSpec(id, frameWidth, frameHeight) {
    this.frameSpecs.set(id, { frameWidth, frameHeight });
  }

  // Source cell size for a sheet; falls back to the whole image when unregistered.
  getFrameSpec(id) {
    const spec = this.frameSpecs.get(id);
    if (spec) return spec;

    const img = this.getTexture(id);
    if (!img) return null;
    return { frameWidth: img.naturalWidth, frameHeight: img.naturalHeight };
  }

  // Destination size that preserves a sheet frame's native aspect ratio.
  getFrameSize(id, scale = 1) {
    const spec = this.getFrameSpec(id);
    if (!spec) return null;
    return { width: spec.frameWidth * scale, height: spec.frameHeight * scale };
  }

  draw(id, x, y, width, height, ctx, flipHorizontal = false) {
    const img = this.getTexture(id);
    if (!img) {
      ctx.fillStyle = '#ff00ff';
      ctx.fillRect(x, y, width, height);
      return;
    }

    ctx.save();
    if (flipHorizontal) {
      ctx.translate(x + width, y);
      ctx.scale(-1, 1);
      ctx.drawImage(img, 0, 0, width, height);
    } else {
      ctx.drawImage(img, x, y, width, height);
    }
    ctx.restore();
  }

  drawFrame(id, x, y, width, height, currentRow, currentFrame, ctx, angle = 0, alpha = 1.0, flipHorizontal = false) {
    const img = this.getTexture(id);
    if (!img) {
      ctx.fillStyle = '#ff00ff';
      ctx.fillRect(x, y, width, height);
      return;
    }

    const spec = this.getFrameSpec(id);
    const srcW = spec ? spec.frameWidth : img.naturalWidth;
    const srcH = spec ? spec.frameHeight : img.naturalHeight;
    const srcX = Math.min(srcW * currentFrame, Math.max(0, img.naturalWidth - srcW));
    const srcY = Math.min(srcH * currentRow, Math.max(0, img.naturalHeight - srcH));

    ctx.save();
    ctx.globalAlpha = alpha;

    ctx.translate(x + width / 2, y + height / 2);
    if (angle !== 0) {
      ctx.rotate((angle * Math.PI) / 180);
    }
    if (flipHorizontal) {
      ctx.scale(-1, 1);
    }

    ctx.drawImage(img, srcX, srcY, srcW, srcH, -width / 2, -height / 2, width, height);
    ctx.restore();
  }

  drawTile(id, margin, spacing, x, y, width, height, currentRow, currentFrame, ctx) {
    const img = this.getTexture(id);
    if (!img) return;

    const srcX = margin + (spacing + width) * currentFrame;
    const srcY = margin + (spacing + height) * currentRow;

    ctx.drawImage(img, srcX, srcY, width, height, x, y, width, height);
  }
}

export const TheTextureManager = TextureManager.getInstance();
