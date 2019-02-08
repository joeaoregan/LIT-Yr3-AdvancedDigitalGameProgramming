/*	
	MiniMap.h

	Created by:		Joe O'Regan
	Student Number:	K00203642

	Done:
		2017/04/23	Added Mini Map to keep track of player progress
*/

#ifndef MINI_MAP_H
#define MINI_MAP_H

#include "ShooterObject.h"
#include "GameObjectFactory.h"

class MiniMap : public ShooterObject {
public:
	SDL_Rect miniMapViewport = { 100, 580, 600, 60 };				// 2017/04/23	Mini Map Display viewport

	virtual ~MiniMap() {}

	MiniMap() {
		std::cout << "Mini Map created" << std::endl;
		m_bDead = false;
	}

	virtual void load(std::unique_ptr<LoaderParams> const &pParams) {
		ShooterObject::load(std::move(pParams));
	}
	virtual void update() {}	// Player ship coordinates updated in Player.cpp, and stored in Game.cpp for access

	virtual void draw() {
		//SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 255, 0, 0, 255);										// Set colour for box outlines red // Goes mental
		SDL_RenderDrawRect(Game::Instance()->getRenderer(), &miniMapViewport);											// Draw squares around the Player 1 viewports
		SDL_RenderSetViewport(Game::Instance()->getRenderer(), &miniMapViewport);										// 2017/04/23 Set the viewport to the mini map

		//Texture::Instance()->draw("mapID", 0, 0, 600, 60, Game::Instance()->getRenderer());
		//Texture::Instance()->draw("mapHeliID", Game::Instance()->playerMapX / 8, Game::Instance()->playerY / 8, 13, 5, Game::Instance()->getRenderer());	// Map is 1/8 size, so helicopter and coordinates are 1/8 size
		Texture::Instance()->draw("minimap", 0, 0, 600, 60, Game::Instance()->getRenderer());																// 2017/04/23 minimap
		Texture::Instance()->draw("miniheli", Game::Instance()->playerMapX / 8, Game::Instance()->playerY / 8, 13, 5, Game::Instance()->getRenderer());	// Map is 1/8 size, so helicopter and coordinates are 1/8 size
	}
	virtual void collision() {}										// Can't collide, as in HUD
	virtual void clean() {
		Texture::Instance()->clearFromTextureMap("mapID");			// Clear the images
		Texture::Instance()->clearFromTextureMap("mapHeliID");
	}

	virtual std::string type() { return "MiniMap"; }
};

class MiniMapCreator : public BaseCreator {
	GameObject* createGameObject() const {
		return new MiniMap();
	}
};

#endif
