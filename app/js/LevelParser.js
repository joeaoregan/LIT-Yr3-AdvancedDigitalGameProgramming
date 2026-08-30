import { Glider, AngryGlider, ShotGlider, Turret, RoofTurret, Level1Boss, PowerUp, Pounder, Squasher, Eskeletor } from './entities/Enemies.js';
import { TileLayer } from './TileLayer.js';

export class LevelParser {
  async decodeZlibBase64(base64Str, width, height) {
    const binaryStr = atob(base64Str.trim().replace(/\s+/g, ''));
    const bytes = new Uint8Array(binaryStr.length);
    for (let i = 0; i < binaryStr.length; i++) {
      bytes[i] = binaryStr.charCodeAt(i);
    }

    const ds = new DecompressionStream('deflate');
    const writer = ds.writable.getWriter();
    writer.write(bytes);
    writer.close();
    const buffer = await new Response(ds.readable).arrayBuffer();
    const rawIDs = new Int32Array(buffer);

    const grid = [];
    for (let r = 0; r < height; r++) {
      const row = [];
      for (let c = 0; c < width; c++) {
        row.push(rawIDs[r * width + c] || 0);
      }
      grid.push(row);
    }
    return grid;
  }

  async parseLevel(mapPath) {
    try {
      const response = await fetch(mapPath);
      const xmlText = await response.text();
      const parser = new DOMParser();
      const xmlDoc = parser.parseFromString(xmlText, 'text/xml');

      const mapElem = xmlDoc.querySelector('map');
      const width = parseInt(mapElem.getAttribute('width')) || 150;
      const height = parseInt(mapElem.getAttribute('height')) || 15;
      const tileWidth = parseInt(mapElem.getAttribute('tilewidth')) || 32;
      const tileHeight = parseInt(mapElem.getAttribute('tileheight')) || 32;

      // Parse Tilesets
      const tilesets = [];
      const tilesetNodes = xmlDoc.querySelectorAll('tileset');
      tilesetNodes.forEach((t) => {
        const firstGridID = parseInt(t.getAttribute('firstgid'));
        const name = t.getAttribute('name');
        const tw = parseInt(t.getAttribute('tilewidth'));
        const th = parseInt(t.getAttribute('tileheight'));
        const spacing = parseInt(t.getAttribute('spacing') || 0);
        const margin = parseInt(t.getAttribute('margin') || 0);
        const columns = parseInt(t.getAttribute('columns') || 15);

        tilesets.push({
          firstGridID,
          name,
          tileWidth: tw,
          tileHeight: th,
          spacing,
          margin,
          numColumns: columns
        });
      });

      // Parse Tile Layers
      const tileLayers = [];
      const layerNodes = xmlDoc.querySelectorAll('layer');
      for (const layerElem of layerNodes) {
        const dataNode = layerElem.querySelector('data');
        if (dataNode?.textContent) {
          const encoding = dataNode.getAttribute('encoding');
          const compression = dataNode.getAttribute('compression');

          if (encoding === 'base64' && compression === 'zlib') {
            // Layers can be shorter than the map bounds, so use their own dimensions
            const layerWidth = Number.parseInt(layerElem.getAttribute('width')) || width;
            const layerHeight = Number.parseInt(layerElem.getAttribute('height')) || height;
            const grid = await this.decodeZlibBase64(dataNode.textContent, layerWidth, layerHeight);
            const tileLayer = new TileLayer(tileWidth, tilesets);
            tileLayer.setTileIDs(grid);
            tileLayer.collidable = layerElem.querySelector('property[name="collidable"]') !== null;
            tileLayers.push(tileLayer);
          }
        }
      }

      // Parse Object Layers (Enemies / Player spawn points)
      const spawnedObjects = [];
      const objectGroups = xmlDoc.querySelectorAll('objectgroup');
      objectGroups.forEach((group) => {
        const offsetX = parseFloat(group.getAttribute('offsetx') || 0);
        const offsetY = parseFloat(group.getAttribute('offsety') || 0);
        const objects = group.querySelectorAll('object');
        objects.forEach((obj) => {
          const type = obj.getAttribute('type');
          const x = parseFloat(obj.getAttribute('x')) + offsetX;
          const y = parseFloat(obj.getAttribute('y')) + offsetY;

          let entity = null;
          if (type === 'Glider') entity = new Glider(x, y);
          else if (type === 'AngryGlider') entity = new AngryGlider(x, y);
          else if (type === 'ShotGlider') entity = new ShotGlider(x, y);
          else if (type === 'Turret') entity = new Turret(x, y);
          else if (type === 'RoofTurret') entity = new RoofTurret(x, y);
          else if (type === 'Pounder') entity = new Pounder(x, y);
          else if (type === 'Squasher') entity = new Squasher(x, y);
          else if (type === 'Eskeletor') entity = new Eskeletor(x, y);
          else if (type === 'Boss' || type === 'Level1Boss') entity = new Level1Boss(x, y);
          else if (type === 'PowerUp') entity = new PowerUp(x, y);

          if (entity) {
            entity.mapX = x;
            spawnedObjects.push(entity);
          }
        });
      });

      return {
        width,
        height,
        tileWidth,
        tileHeight,
        tileLayers,
        spawnedObjects
      };
    } catch (e) {
      console.warn(`Could not parse map file: ${mapPath}`, e);
      return null;
    }
  }
}

