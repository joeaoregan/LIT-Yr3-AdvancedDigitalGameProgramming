/*
//  TileLayer.cpp
//  SDL Game Programming Book
//
//  Created by shaun mitchell on 10/03/2013.
//  Copyright (c) 2013 shaun mitchell. All rights reserved.

	Modified by:	Joe O'Regan
	Student Number:	K00203642

	Done:
		2017/04/22	Set the scrolling as stopped or moving for mini map
*/


#include "TileLayer.h"
#include "TextureManager.h"
#include "Game.h"

SDL_Rect tiledViewport;				// 2017/04/22 Main game screen view port, this is the section of the window where the game is rendered

TileLayer::TileLayer(int tileSize, const std::vector<Tileset>& tilesets) : m_tileSize(tileSize), m_tilesets(tilesets), m_position(0,0), m_velocity(0,0) {
    m_numColumns = (TheGame::Instance()->getGameWidth() / m_tileSize) + 1;
    m_numRows = (TheGame::Instance()->getGameHeight() / m_tileSize);
}

void TileLayer::update(Level* pLevel) {
    if(m_position.getX() < ((m_mapWidth * m_tileSize) - TheGame::Instance()->getGameWidth()) - m_tileSize) {
        m_velocity.setX(TheGame::Instance()->getScrollSpeed());
        m_position += m_velocity;
		Game::Instance()->stillScrolling = true;	// 2017/04/22 Set the scrolling as stopped or moving for mini map
    }
    else {
        m_velocity.setX(0);
		Game::Instance()->stillScrolling = false;	// 2017/04/22 Set the scrolling as stopped or moving for mini map
    }
}

void TileLayer::render() {
	tiledViewport = { 0, 0, 800, 480 };
	SDL_RenderSetViewport(Game::Instance()->getRenderer(), &tiledViewport);						// Clear the current viewport to render to full window / screen
   
	int x, y, x2, y2 = 0;
    
    x = m_position.getX() / m_tileSize;
    y = m_position.getY() / m_tileSize;
    
    x2 = int(m_position.getX()) % m_tileSize;
    y2 = int(m_position.getY()) % m_tileSize;
    
    for(int i = 0; i < m_numRows; i++) {
        for(int j = 0; j < m_numColumns; j++) {
            int id = m_tileIDs[i + y][j + x];
            
            if(id == 0)  {
                continue;
            }
            
            Tileset tileset = getTilesetByID(id);
            
            id--;
            
            TheTextureManager::Instance()->drawTile(tileset.name, tileset.margin, tileset.spacing, (j * m_tileSize) - x2, (i * m_tileSize) - y2, m_tileSize, m_tileSize, (id - (tileset.firstGridID - 1)) / tileset.numColumns, (id - (tileset.firstGridID - 1)) % tileset.numColumns, TheGame::Instance()->getRenderer());
        }
    }
}

Tileset TileLayer::getTilesetByID(int tileID) {
    for(int i = 0; i < m_tilesets.size(); i++) {
        if( i + 1 <= m_tilesets.size() - 1) {
            if(tileID >= m_tilesets[i].firstGridID && tileID < m_tilesets[i + 1].firstGridID) {
                return m_tilesets[i];
            }
        }
        else {
            return m_tilesets[i];
        }
    }
    
    std::cout << "did not find tileset, returning empty tileset\n";
    Tileset t;
    return t;
}