/*	
	HUD.h

	Created by:		Joe O'Regan
	Student Number:	K00203642

	Done:
		2017/04/23	Added Heads Up Display panel at bottom of game screen
*/

#ifndef HUD_H
#define HUD_H

#include "ShooterObject.h"
#include "GameObjectFactory.h"
#include "TextureManager.h"		// Draw lives

class HUD : public ShooterObject {
public:
	SDL_Rect hudViewport = { 0, 480, 800, 160 };				// 2017/04/23	Mini Map Display viewport

	virtual ~HUD() {}

	HUD() {
		std::cout << "Heads Up Display created" << std::endl;
		m_bDead = false;
	}

	virtual void load(std::unique_ptr<LoaderParams> const &pParams) {
		ShooterObject::load(std::move(pParams));
		//Texture::Instance()->loadLevelText("Level " + std::to_string(Game::Instance()->getCurrentLevel()));	// 2017/04/22 Changed to show current level number
	}

	virtual void update() {}

	SDL_Texture* tx1 = 0;
	int prevTurrets = -1;	// Don't render the text every frame

	virtual void draw() {
		SDL_RenderSetViewport(Game::Instance()->getRenderer(), &hudViewport);								// 2017/04/22 Set the viewport to Game Screen// Draw Lives

		// Draw Lives
		for (int i = 0; i < TheGame::Instance()->getPlayerLives(); i++) {
			TextureManager::Instance()->drawFrame("lives", i * 30, 0, 32, 30, 0, 0, TheGame::Instance()->getRenderer(), 0.0, 255);
		}

		Texture::Instance()->drawText("levelID", 120, 0, Game::Instance()->getRenderer());

		// Display number of turrets destroyed
		//Texture::Instance()->turretsKilledText("");														// Render the number of turrets destroyed

		if (prevTurrets != Game::Instance()->turretKills) {
			std::string turrets = "Turrets: " + std::to_string(Game::Instance()->turretKills);
			Texture::Instance()->createText(tx1, turrets + "/7", "turretsKilledID", { 0, 0, 0, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 20), Game::Instance()->getRenderer(), true);		// Get ready to start message
		}

		Texture::Instance()->drawText("turretsKilledID", 120, 50, Game::Instance()->getRenderer());

		SDL_RenderSetViewport(Game::Instance()->getRenderer(), NULL);										// 2017/04/23 Clear the viewport
	}
	virtual void collision() {}																				// Can't collide, as not in game screen
	virtual void clean() {}

	virtual std::string type() { return "HUD"; }
};

class HUDCreator : public BaseCreator {
	GameObject* createGameObject() const {
		return new HUD();
	}
};

#endif
