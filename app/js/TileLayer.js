import { TheTextureManager } from './TextureManager.js';

export class TileLayer {
  constructor(tileSize, tilesets) {
    this.tileSize = tileSize;
    this.tilesets = tilesets;
    this.tileIDs = [];
    this.mapWidth = 0;
    this.mapHeight = 0;
    this.collidable = false;
  }

  setTileIDs(data) {
    this.tileIDs = data;
    this.mapHeight = data.length;
    this.mapWidth = data.length > 0 ? data[0].length : 0;
  }

  getTilesetByID(tileID) {
    for (let i = 0; i < this.tilesets.length; i++) {
      if (i + 1 < this.tilesets.length) {
        if (tileID >= this.tilesets[i].firstGridID && tileID < this.tilesets[i + 1].firstGridID) {
          return this.tilesets[i];
        }
      } else {
        return this.tilesets[i];
      }
    }
    return this.tilesets[0];
  }

  render(ctx, scrollX) {
    if (!this.tileIDs || this.tileIDs.length === 0) return;

    const startCol = Math.floor(scrollX / this.tileSize);
    const endCol = Math.min(this.mapWidth, startCol + Math.ceil(960 / this.tileSize) + 2);
    const offsetX = Math.floor(scrollX % this.tileSize);

    for (let r = 0; r < this.mapHeight; r++) {
      for (let c = startCol; c < endCol; c++) {
        if (c < 0 || c >= this.mapWidth) continue;
        const id = this.tileIDs[r][c];
        if (id === 0) continue;

        const tileset = this.getTilesetByID(id);
        const tileIndex = id - tileset.firstGridID;
        const row = Math.floor(tileIndex / tileset.numColumns);
        const col = tileIndex % tileset.numColumns;

        const screenX = (c - startCol) * this.tileSize - offsetX;
        const screenY = r * this.tileSize;

        TheTextureManager.drawTile(
          tileset.name,
          tileset.margin,
          tileset.spacing,
          screenX,
          screenY,
          this.tileSize,
          this.tileSize,
          row,
          col,
          ctx
        );
      }
    }
  }
}
